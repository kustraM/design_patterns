/**
 * @file abstract_factory_myproject.cpp
 * @author mkustra
 * @brief Użycie wzorca projektowego fabryki abstrakcyjnej w cpp, przerobiony przykład ze strony refactoring.guru
 * Uzupełnienie terści o dodanie produktu C oraz trzeciej fabryki dla produktow A3 i B3 (C3 nie istnieje ).
 * Produkty C są powiązane z produktami A i B.
 *
 * @version 1.0
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 * @result
Client: Testing client code with the first factory type:
The result of the product B1.
The result of the B1 collaborating with ( The result of the product A1. )
The result of the product C1.
The result of the C1 collaborating with ( The result of the product A1. )
The result of the C1 collaborating with ( The result of the product B1. )

Client: Testing the same client code with the second factory type:
The result of the product B2.
The result of the B2 collaborating with ( The result of the product A2. )
The result of the product C2.
The result of the C2 collaborating with ( The result of the product A2. )
The result of the C2 collaborating with ( The result of the product B2. )

Client: Testing the same client code with the third factory type:
The result of the product B3.
The result of the B3 collaborating with ( The result of the product A3. )

 */

#include <iostream>
/**
 * każdy z produktów danej fabryki ma jakiś interface.
 * konkretne produkty muszą dziedziczyć ten interface
 *
 */
class AbstractProductA
{
public:
    virtual ~AbstractProductA(){};
    virtual std::string UsefulFunctionA() const = 0;
};

/**
 * konkretne produkty o pewnym interface
 *
 */
class ConcreteProductA1 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A1.";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A2.";
    }
};

class ConcreteProductA3 : public AbstractProductA
{
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A3.";
    }
};
/**
 * Kolejny produkt, produkt B, zasada działania taka sama jak w poprzednim przypadku
 *
 */
class AbstractProductB
{
public:
    virtual ~AbstractProductB(){};
    virtual std::string UsefulFunctionB() const = 0;
    /**
     * Współpraca z produktem A, funkcja wirtualna, która jest nadpisywana w kolejnych klasach ConcreteProduct
     *
     */
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B1.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B2.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

class ConcreteProductB3 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B3.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B3 collaborating with ( " + result + " )";
    }
};
/**
 * tak samo jak w przypadku AbstractProductB
 *
 */
class AbstractProductC
{
public:
    virtual ~AbstractProductC(){};
    virtual std::string UsefulFunctionC() const = 0;
    virtual std::string AnotherUsefulFunctionC(const AbstractProductA &collaborator) const = 0;
    /**
     * współpraca produktu C z produktem B
     *
     */
    virtual std::string SecondAnotherUsefulFunctionC(const AbstractProductB &collaborator) const = 0;
};

class ConcreteProductC1 : public AbstractProductC
{
public:
    std::string UsefulFunctionC() const override
    {
        return "The result of the product C1.";
    }

    std::string AnotherUsefulFunctionC(const AbstractProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the C1 collaborating with ( " + result + " )";
    }
    std::string SecondAnotherUsefulFunctionC(const AbstractProductB &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionB();
        return "The result of the C1 collaborating with ( " + result + " )";
    }
};
class ConcreteProductC2 : public AbstractProductC
{
public:
    std::string UsefulFunctionC() const override
    {
        return "The result of the product C2.";
    }

    std::string AnotherUsefulFunctionC(const AbstractProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the C2 collaborating with ( " + result + " )";
    }

    std::string SecondAnotherUsefulFunctionC(const AbstractProductB &collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionB();
        return "The result of the C2 collaborating with ( " + result + " )";
    }
};

/**
 * Fabryka abstrakcyjna zwraca abstrakcyjne produkty
 *
 */

class AbstractFactory
{
public:
    virtual AbstractProductA *CreateProductA() const = 0;
    virtual AbstractProductB *CreateProductB() const = 0;
    virtual AbstractProductC *CreateProductC() const = 0;
};

/**
 * Poszczególne fabryki produkują rodzinę produktów należących do jednego wariantu.
 * Fabryka gwarantuje, że powstałe produkty są ze sobą kompatybilne.
 *
 */
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA() const override
    {
        return new ConcreteProductA1();
    }
    /**
     * Funkcje metod fabryki zwracają abstrakcyjny produkt,
     * podczas gdy wewnątrz metody powstaje konkretny produkt.
     */
    AbstractProductB *CreateProductB() const override
    {
        return new ConcreteProductB1();
    }

    AbstractProductC *CreateProductC() const override
    {
        return new ConcreteProductC1();
    }
};

/**
 * To samo co w przypadku wyżej
 */
class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA() const override
    {
        return new ConcreteProductA2();
    }
    AbstractProductB *CreateProductB() const override
    {
        return new ConcreteProductB2();
    }
    AbstractProductC *CreateProductC() const override
    {
        return new ConcreteProductC2();
    }
};

class ConcreteFactory3 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA() const override
    {
        return new ConcreteProductA3();
    }
    AbstractProductB *CreateProductB() const override
    {
        return new ConcreteProductB3();
    }

    AbstractProductC *CreateProductC() const override
    {
        return 0;
    }
};

/**
 * Kod klienta działa z fabrykami i produktami tylko poprzez typy abstrakcyjne: AbstractFactory i AbstractProduct.
 * Pozwala to przekazać dowolną podklasę fabryki lub produktu do kodu klienta.
 */

void ClientCode(const AbstractFactory &factory)
{
    const AbstractProductA *product_a = factory.CreateProductA();
    const AbstractProductB *product_b = factory.CreateProductB();
    const AbstractProductC *product_c = factory.CreateProductC();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    std::cout << product_c->UsefulFunctionC() << "\n";
    std::cout << product_c->AnotherUsefulFunctionC(*product_a) << "\n";
    std::cout << product_c->SecondAnotherUsefulFunctionC(*product_b) << "\n";
    delete product_a;
    delete product_b;
    delete product_c;
}

int main()
{
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the third factory type:\n";
    ConcreteFactory3 *f3 = new ConcreteFactory3();
    ClientCode(*f3);
    delete f3;
    return 0;
}
