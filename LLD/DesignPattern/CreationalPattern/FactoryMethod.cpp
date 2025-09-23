/*
FACTORY METHOD

It is really useful when we want to decouple what a client needs from how the object is created.

1) Intuition and Intent
 Define an interface to create an object, but let subclasses decide whether which concrete class to instantiate

 - Product -> Interface/abstract base
 - Concrete Product -> concrete implementation of the product
 - Creator -> declares the factory method that returns a product
 - Concrete creator -> overrides the factory method to return a particular Concrete Product.

 */

 #include <iostream>
 #include <memory>

 using namespace std;

 //Product Interface
 struct Document
 {
    virtual ~Document() = default;
    virtual void open() = 0;
 };

 //Concrete Interface
 struct PdfDocument: Document
 {
    void open() override
    { cout << "Opening PDF document\n";};
 };

 struct WordDocument: Document
 {
    void open() override
    {
        cout << "Opening Word document\n";
    };
 };

 //Creator
 struct Application
 {
    virtual ~Application() = default;

    //factory method (virtual)
    virtual unique_ptr<Document> createDocument() = 0;

    // business logic that uses product
    void openDoc()
    {
        auto doc = createDocument();
        doc->open();
    }
 };

 //Concrete Creator
struct PdfApp : Application
{
    unique_ptr<Document> createDocument() override{
        return make_unique<PdfDocument>();
    }
};

 struct WordApp : Application
 {
    unique_ptr<Document> createDocument() override
    {
        return make_unique<WordDocument>();
    }
 };

 int main()
 {
    PdfApp pdfApp;
    WordApp wordApp;

    pdfApp.openDoc();
    wordApp.openDoc();

 }

 // PROS
 /*
 - Decouples creation from usage
 - Supports Open/Closed
 - Encapsulates creation logic at one place
 - Good for polymorphic creation and hiding concrete class details.
 */

 //CONS
 /*
 - More classes to deal with
 */

 // Now if we have to add a third app let's say excel, we just need to add new classes and it is ready
 /*
 struct ExcelDocument: Document {}
 struct ExcelApp: Application {}
 */
