/**
 * @file factory_method_myproject.cpp
 * @author mkustra
 * @brief Użycie wzorca projektowego metody wytwórczej w cpp, przerobiony przykład ze strony refactoring.guru
 * @version 1.0
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
/**
 * Ogólny interface produktu
 */

class Product
{
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

/**
 * ConcreteProduct zapewniają różne implementacje interfejsu Product.
 */
class ConcreteProduct1 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct1}";
    }
};
class ConcreteProduct2 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct2}";
    }
};

class ConcreteProduct3 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct3}";
    }
};

/**
 * klasa Creator deklaruje metodę fabryczną, która ma zwrócić obiekt klasy Product. Podklasy Creator zwykle zapewniają implementację tej metody.
 */
class Creator
{
public:
    virtual ~Creator(){};
    virtual Product *FactoryMethod() const = 0;
    std::string SomeOperation() const
    {
        // Wywołaj FactoryMethod, aby utworzyć obiekt product.
        Product *product = this->FactoryMethod();
        std::string result = "The same creator's code working with " + product->Operation();
        delete product;
        return result;
    }
};

/**
 * ConcreteCreator zastępuje metode Creator, aby zmienić typ produktu
 */
class ConcreteCreator1 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct2();
    }
};

class ConcreteCreator3 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct3();
    }
};

/**
 * ClientCode poprzez Creator (ogólnym interface) współpracuje z konkretnym interface
 */
void ClientCode(const Creator &creator)
{
    std::cout << "Connect with interface.\n"
              << creator.SomeOperation() << std::endl;
}

/**
 * Wybór z jaką aplikacją będzie nawiązywane połączenie
 */

int main()
{
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator *creator = new ConcreteCreator1();
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator3.\n";
    Creator *creator3 = new ConcreteCreator3();
    ClientCode(*creator3);

    delete creator;
    delete creator2;
    delete creator3;
    return 0;
}