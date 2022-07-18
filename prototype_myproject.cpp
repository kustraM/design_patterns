/**
 * @file prototype_myproject.cpp
 * @author mkustra
 * @brief Użycie wzorca projektowego prototyp w cpp, przerobiony przykład ze strony refactoring.guru
 * Dodanie Prototype 3 oraz id (string) do każdego prototypu
 * @version 1.0
 * @date 2022-06-28
 *
 * @copyright Copyright (c) 2022
 *
 * @result
Making prototypes
Method from PROTOTYPE_1  with field: 90 with id: 192.168.21.1
Method from PROTOTYPE_2  with field: 10 with id: 192.168.21.2
Method from PROTOTYPE_3  with field: 40 with id: 192.168.21.3
 *
 */

#include <iostream>
#include <unordered_map>
using std::string;

enum Type
{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2,
    PROTOTYPE_3
};

/**
 * @brief Przykładowa klasa, która ma zdolność klonowania.
 *
 *
 */
class Prototype
{
protected:
    string prototype_name_;
    float prototype_field_;
    string prototype_id_;

public:
    Prototype() {}
    Prototype(string prototype_name)
        : prototype_name_(prototype_name)
    {
    }

    virtual ~Prototype() {}
    virtual Prototype *Clone() const = 0;
    virtual void Method(float prototype_field, string prototype_id)
    {
        this->prototype_field_ = prototype_field;
        std::cout << "Method from " << prototype_name_ << " with field: " << prototype_field << " with id: " << prototype_id << std::endl;
    }
};

/**
 * @brief Konkretne trzy prototypy dziedziczące po klasie Prototype, identyczna budowa
 *
 */

class ConcretePrototype1 : public Prototype
{
private:
    float concrete_prototype_field1_;
    string concrete_prototype_id1_;

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field, string concrete_prototype_id)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field), concrete_prototype_id1_(concrete_prototype_id)
    {
    }

    Prototype *Clone() const override
    {
        return new ConcretePrototype1(*this); // zwolnienie pamięci po stronie klienta
    }
};

class ConcretePrototype2 : public Prototype
{
private:
    float concrete_prototype_field2_;
    string concrete_prototype_id2_;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field, string concrete_prototype_id)
        : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field), concrete_prototype_id2_(concrete_prototype_id)
    {
    }
    Prototype *Clone() const override
    {
        return new ConcretePrototype2(*this);
    }
};

class ConcretePrototype3 : public Prototype
{
private:
    float concrete_prototype_field1_;
    string concrete_prototype_id3_;

public:
    ConcretePrototype3(string prototype_name, float concrete_prototype_field, string concrete_prototype_id)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field), concrete_prototype_id3_(concrete_prototype_id)
    {
    }

    Prototype *Clone() const override
    {
        return new ConcretePrototype3(*this);
    }
};

/**
 * @brief Fabryka prototypów, w którym tworzone są 3 prototypy
 * float concrete_prototype_field, std::string concrete_prototype_id dowolne
 *
 */

class PrototypeFactory
{
private:
    std::unordered_map<Type, Prototype *, std::hash<int>> prototypes_;

public:
    PrototypeFactory()
    {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 0.f, "");
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 0.f, "");
        prototypes_[Type::PROTOTYPE_3] = new ConcretePrototype3("PROTOTYPE_3 ", 0.f, "");
    }

    ~PrototypeFactory()
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
        delete prototypes_[Type::PROTOTYPE_3];
    }

    /**
     * @brief Określenie typu prototypu; metoda "sama" tworzy obiekt o tym typie
     *
     */

    Prototype *CreatePrototype(Type type)
    {
        return prototypes_[type]->Clone();
    }
};
/**
 * @brief Klasa klienta; Tworzenie prototypów, wywoływanie metody i usuwanie prototypów po stronie klienta
 *
 * @param prototype_factory
 */

void Client(PrototypeFactory &prototype_factory)
{
    std::cout << "Making prototypes" << std::endl;

    Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90, "192.168.21.1");
    delete prototype;

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10, "192.168.21.2");
    delete prototype;

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_3);
    prototype->Method(40, "192.168.21.3");
    delete prototype;
}

int main()
{
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;
    return 0;
}