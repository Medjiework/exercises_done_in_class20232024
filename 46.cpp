#include <iostream>
using namespace std;

class Gate {
public:
    Gate *input[2] = {nullptr, nullptr};
    virtual bool output() = 0;
    virtual void setValue(Gate *gate, int pin);
    virtual void setValue(bool, int);
};

class TRUE : public Gate {
public:
    bool output() override { return true; }
    void setValue(Gate *, int) override {}
    void setValue(bool, int) override {}
};

class FALSE : public Gate {
public:
    bool output() override { return false; }
    void setValue(Gate *, int) override {}
    void setValue(bool, int) override {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin) {
    if (val) this->input[pin] = &t;
    else this->input[pin] = &f;
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate {
public:
    bool output() override { return !(this->input[0]->output()); }
    void setValue(bool val, int pin = 0) override {
        if (val) this->input[0] = &t;
        else this->input[0] = &f;
    }
    void setValue(Gate *gate, int pin = 0) override { this->input[0] = gate; }
};

class NAND : public Gate {
public:
    bool output() override { return !(this->input[0]->output() && this->input[1]->output()); }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override {
        if(val) this->input[pin] = &t;
        else this->input[pin] = &f;
    }
};

class NOR : public Gate {
public:
    bool output() override { return !(this->input[0]->output() || this->input[1]->output()); }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override {
        if(val) this->input[pin] = &t;
        else this->input[pin] = &f;
    }
};

class AND : public Gate {
public:
    AND() {
        component[0] = new NAND();
        component[1] = new NOT();
    }
    bool output() override {
        component[0]->input[0] = this->input[0];
        component[0]->input[1] = this->input[1];
        component[1]->input[0] = component[0];
        return component[1]->output();
    }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override {
        if (val) this->input[pin] = &t;
        else this->input[pin] = &f;
    }
private:
    Gate *component[2];
};

class OR : public Gate {
public:
    OR() {
        component[0] = new NOR();
        component[1] = new NOT();
    }
    bool output() override {
        component[0]->input[0] = this->input[0];
        component[0]->input[1] = this->input[1];
        component[1]->input[0] = component[0];
        return component[1]->output();
    }
    void setValue(Gate *gate, int pin) override { this->input[pin] = gate; }
    void setValue(bool val, int pin) override {
        if (val) this->input[pin] = &t;
        else this->input[pin] = &f;
    }
private:
    Gate *component[2];
};

class Mux {
public:
    virtual void setData(bool, int) = 0;
    virtual void setData(Gate *, int) = 0;
    virtual void setEnable(bool) = 0;
    virtual void setEnable(Gate *) = 0;
    virtual void setSelect(bool, int) = 0;
    virtual void setSelect(Gate *, int) = 0;
    virtual Gate *output() = 0;
protected:
    Gate *enable;
};

class Mux2_1 : public Mux {
public:
    Mux2_1() : Mux2_1(0) {}
    Mux2_1(bool val) {
        if(val) this->enable = &t;
        else this->enable = &f;
        component[0] = new AND;
        component[1] = new AND;
        component[2] = new NOT;
        component[3] = new OR;
        component[4] = new AND;
    }
    void setData(bool val, int pin) override {
        switch(pin) {
            case 0 : component[0]->setValue(val, 0); break;
            case 1 : component[1]->setValue(val, 0); break;
            default : ;
        }
    }
    void setData(Gate *gate, int pin) override {
        switch(pin) {
            case 0 : component[0]->setValue(gate, 0); break;
            case 1 : component[1]->setValue(gate, 0); break;
            default : ;
        }
    }
    void setEnable(bool val) override {
        if(val) this->enable = &t;
        else this->enable = &f;
    }
    void setEnable(Gate *gate) override {
        this->enable = gate;
    }
    void setSelect(bool val, int pin = 0) override {
        component[1]->setValue(val, 1);
        component[2]->setValue(val, 0);
        component[0]->input[1] = component[2];
    }
    void setSelect(Gate *gate, int pin = 0) override {
        component[1]->setValue(gate, 1);
        component[2]->setValue(gate, 0);
        component[0]->input[1] = component[2];
    }
    Gate *output() override {
        component[3]->setValue(component[0], 0);
        component[3]->setValue(component[1], 1);
        component[4]->setValue(this->enable, 0);
        component[4]->setValue(component[3], 1);
        return component[4];
    }
private:
    Gate *component[5];
};

class Mux4_1 : public Mux {
public:
    Mux4_1() {}
    Mux4_1(bool val) {
        mux2_1[0] = new Mux2_1(val);
        mux2_1[1] = new Mux2_1(val);
        mux2_1[2] = new Mux2_1(val);
    }
    void setData(bool val, int pin) override {
        if (pin < 2)
            mux2_1[0]->setData(val, pin);
        else
            mux2_1[1]->setData(val, pin - 2);
    }
    void setData(Gate *gate, int pin) override {
        if (pin < 2)
            mux2_1[0]->setData(gate, pin);
        else
            mux2_1[1]->setData(gate, pin - 2);
    }
    void setEnable(bool val) override {
        for (int i = 0; i < 3; ++i)
            mux2_1[i]->setEnable(val);
    }
    void setEnable(Gate *gate) override {
        for (int i = 0; i < 3; ++i)
            mux2_1[i]->setEnable(gate);
    }
    void setSelect(bool val, int pin) override {
        if (pin == 0) {
            mux2_1[0]->setSelect(val, 0);
            mux2_1[1]->setSelect(val, 0);
        } else {
            mux2_1[2]->setSelect(val, 0);
        }
    }
    void setSelect(Gate *gate, int pin) override {
        if (pin == 0) {
            mux2_1[0]->setSelect(gate, 0);
            mux2_1[1]->setSelect(gate, 0);
        } else {
            mux2_1[2]->setSelect(gate, 0);
        }
    }
    Gate *output() override {
        mux2_1[2]->setData(mux2_1[0]->output(), 0);
        mux2_1[2]->setData(mux2_1[1]->output(), 1);
        return mux2_1[2]->output();
    }
private:
    Mux *mux2_1[3];
};

class XOR_Mux : public Gate {
public:
    XOR_Mux() : mux(true) {
        mux.setEnable(true);
    }
    void setValue(bool val, int pin) override {
        mux.setSelect(val, pin);
    }
    void setValue(Gate *gate, int pin) override {
        mux.setSelect(gate, pin);
    }
    bool output() override {
        mux.setData(false, 0);
        mux.setData(true, 1);
        mux.setData(true, 2);
        mux.setData(false, 3);
        return mux.output()->output();
    }
private:
    Mux4_1 mux;
};

int main()
{
    XOR_Mux xorGate;
 
  	int a, b;
    cin >> a >> b;
  
    xorGate.setValue(a, 0);
    xorGate.setValue(b, 1);

    cout << xorGate.output() << endl;

    return 0;
}
