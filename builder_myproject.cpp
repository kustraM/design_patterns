/**
 * @file builder_myproject.cpp
 * @author mkustra
 * @brief Użycie wzorca projektowego budowniczego w cpp, przerobiony przykład ze strony refactoring.guru
 * Dodanie części części D do projektu oraz stworzenie wariantu BuildHalfFeaturedProduct.
 * Dodanie drugiego wariantu produktu niestandardowego
 *
 * @version 1.0
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 * @result
Standard basic product:
Product parts: PartA1

Standard full featured product:
Product parts: PartA1, PartB1, PartC1, PartD1

Standard half featured product:
Product parts: PartA1, PartD1

Custom product 1:
Product parts: PartA1, PartC1, PartD1

Custom product 2:
Product parts: PartB1, PartC1, PartD1
 */

#include <iostream>
#include <vector>

class Product1
{
public:
    std::vector<std::string> parts_;
    void ListParts() const
    {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++)
        {
            if (parts_[i] == parts_.back())
            {
                std::cout << parts_[i];
            }
            else
            {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};

/**
 * Klasa (interfejs) Builder określa metody tworzenia różnych części obiektów produktu.
 */
class Builder
{
public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0; // metoda tworzenia części A
    virtual void ProducePartB() const = 0; // metoda tworzenia części B
    virtual void ProducePartC() const = 0; // metoda tworzenia części C
    virtual void ProducePartD() const = 0; // metoda tworzenia części D
};
/**
 * Klasy ConcreteBuilder są zgodne z interfejsem Builder i zapewniają określone implementacje etapów budowania.
 */
class ConcreteBuilder1 : public Builder
{
private:
    Product1 *product;

public:
    ConcreteBuilder1()
    {
        this->Reset();
    }

    ~ConcreteBuilder1()
    {
        delete product;
    }

    void Reset()
    {
        this->product = new Product1();
    }

    /**
     * @brief Produkcja poszczególnych części, nadpisanie wirtualnych funkcji
     *
     */
    void ProducePartA() const override
    {
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB() const override
    {
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC() const override
    {
        this->product->parts_.push_back("PartC1");
    }

    void ProducePartD() const override
    {
        this->product->parts_.push_back("PartD1");
    }

    /**
     * @brief Pobranie gotowego produktu o określonej konfiguracji
     *
     * @return Product1*
     */
    Product1 *GetProduct()
    {
        Product1 *result = this->product;
        this->Reset();
        return result;
    }
};

/**
 * Kalsa Director jest odpowiedzialna za konkretne konfiguracje produktów
 */
class Director
{
private:
    Builder *builder;

public:
    void set_builder(Builder *builder)
    {
        this->builder = builder;
    }

    /**
     * Konstrukcja produktów o różnej konfiguracji częściowej
     */
    void BuildMinimalViableProduct()
    {
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedProduct()
    {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
        this->builder->ProducePartD();
    }

    void BuildHalfFeaturedProduct()
    {
        this->builder->ProducePartA();
        this->builder->ProducePartD();
    }
};
/**
 * Kod klienta tworzy obiekt builder, przekazuje go Director, a następnie
 * inicjuje proces budowy. Wynik końcowy jest pobierany z obiektu konstruktora.
 */
void ClientCode(Director &director)
{
    ConcreteBuilder1 *builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();

    Product1 *p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();

    p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard half featured product:\n";
    director.BuildHalfFeaturedProduct();

    p = builder->GetProduct();
    p->ListParts();
    delete p;

    // Builder może być używany bez Director
    std::cout << "Custom product 1:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    builder->ProducePartD();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Custom product 2:\n";
    builder->ProducePartB();
    builder->ProducePartC();
    builder->ProducePartD();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main()
{
    Director *director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}