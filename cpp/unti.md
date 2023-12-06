```cpp
#include <iostream>
#include <string>

class Base {
public:
    Base() {
        std::cout << "Base()" << std::endl;
    }
    Base(const std::string &str) : str_(str) {
        std::cout << "Base(const std::string &s)" << std::endl;
    }
    Base(const Base &b) {
        std::cout << "Base(const Base &b)" << std::endl;
        this->str_ = b.str_;
    }
    Base &operator=(const Base &b) {
        std::cout << "Base &operator=(const Base &b)" << std::endl;
        if (this == &b) {
            return *this;
        }
        this->str_ = b.str_;
        return *this;
    }
    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }
    virtual std::string foo() const = 0;
protected:
    const std::string &getStr() const {
        return this->str_;
    }
private:
    std::string str_;
};

class Derived : public Base {
public:
    Derived() : Base() {
        std::cout << "Derived()" << std::endl;
    }
    Derived(const std::string &str) : Base(str) {
        std::cout << "Derived(const std::string &str)" << std::endl;
    }
    Derived(const Derived &d) : Base(d) {
        std::cout << "Derived(const Derived &d)" << std::endl;
    }
    ~Derived() {
        std::cout << "~Derived()" << std::endl;
    }
    Derived &operator=(const Derived &d) {
        std::cout << "const Derived &operator=(const Derived &d)" << std::endl;
        if (this == &d) {
            return *this;
        }
        Base::operator=(d);
        return *this;
    }
    virtual std::string foo() const override {
        return getStr();
    }
};

int main() {
    Base *d_ptr1 = new Derived("d_ptr1");
    std::cout << d_ptr1->foo() << std::endl;

    Base *d_ptr2 = new Derived(*static_cast<Derived *>(d_ptr1));
    std::cout << d_ptr2->foo() << std::endl;

    Base *d_ptr3 = new Derived("d_ptr3");
    std::cout << d_ptr3->foo() << std::endl;
    d_ptr3 = d_ptr2;
    std::cout << d_ptr3->foo() << std::endl;

    delete d_ptr3;
    delete d_ptr1;

    Derived d1("d1");
    std::cout << d1.foo() << std::endl;
    Derived d2 = d1;
    d2 = d1;
    std::cout << d2.foo() << std::endl;
    return 0;
}
```

