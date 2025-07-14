#include <bits/stdc++.h>
using namespace std;

// 1. DocumentElement (Abstract)
class DocumentElement {
public:
    virtual void Render() const = 0;
    virtual string ToString() const = 0; 
    virtual ~DocumentElement() = default;
};

// 2. TextElement
class TextElement : public DocumentElement {
    string text;
public:
    TextElement(const string& t) : text(t) {}
    void Render() const override {
        cout << "Text: " << text << endl;
    }
    string ToString() const override {
        return "Text: " + text;
    }
};

// 3. ImageElement
class ImageElement : public DocumentElement {
    string imagePath;
public:
    ImageElement(const string& path) : imagePath(path) {}
    void Render() const override {
        cout << "Image: " << imagePath << endl;
    }
    string ToString() const override {
        return "Image: " + imagePath;
    }
};

// 4. Document
class Document {
    vector<shared_ptr<DocumentElement>> elements;
public:
    void AddElement(shared_ptr<DocumentElement> el) {
        elements.push_back(el);
    }
    const vector<shared_ptr<DocumentElement>>& GetElements() const {
        return elements;
    }
};

// 5. Persistence (Abstract)
class Persistence {
public:
    virtual void Save(const Document& doc) const = 0;
    virtual ~Persistence() = default;
};

// 6. FileStorage with file handling
class FileStorage : public Persistence {
public:
    void Save(const Document& doc) const override {
        ofstream file("document.txt");
        if (!file.is_open()) {
            cout << "[FileStorage] Error opening file for writing!" << endl;
            return;
        }
        for (const auto& el : doc.GetElements()) {
            file << el->ToString() << endl;
        }
        file.close();
        cout << "[FileStorage] Document saved to document.txt" << endl;
    }
};

// 7. DBStorage (stub)
class DBStorage : public Persistence {
public:
    void Save(const Document& doc) const override {
        cout << "[DBStorage] Document saved to database (simulated)." << endl;
        // Real DB saving would require a DB library
    }
};

// 8. DocumentRender
class DocumentRender {
    const Document& doc;
public:
    DocumentRender(const Document& d) : doc(d) {}
    void Render() const {
        cout << "--- Document Render ---" << endl;
        for (const auto& el : doc.GetElements()) {
            el->Render();
        }
        cout << "-----------------------" << endl;
    }
};

// 9. DocumentEditor
class DocumentEditor {
    Document& doc;
    shared_ptr<Persistence> storage;
public:
    DocumentEditor(Document& d, shared_ptr<Persistence> s)
        : doc(d), storage(s) {}

    void AddText(const string& text) {
        doc.AddElement(make_shared<TextElement>(text));
    }
    void AddImage(const string& path) {
        doc.AddElement(make_shared<ImageElement>(path));
    }
    void Save() const {
        storage->Save(doc);
    }
};

// 10. Main
int main() {
    Document doc;

    // FileStorage saves to "document.txt"
    shared_ptr<Persistence> storage = make_shared<FileStorage>();
    // If you want DB simulation, uncomment below:
    // shared_ptr<Persistence> storage = make_shared<DBStorage>();

    DocumentEditor editor(doc, storage);
    editor.AddText("Welcome to Google Docs (C++ version)!");
    editor.AddImage("pic1.png");
    editor.AddText("This is the end of the document.");
    editor.Save();

    DocumentRender renderer(doc);
    renderer.Render();

    // Let user know document was written to file
    cout << "Check 'document.txt' for file output!" << endl;

    return 0;
}
