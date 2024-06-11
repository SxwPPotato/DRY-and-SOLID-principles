#include <iostream>
#include <fstream>
#include <string>

class Printable
{
public:
    virtual ~Printable() = default;

};

class HTML : public Printable {
public:
    virtual ~HTML() = default;
    virtual std::string printAsHTML() const = 0;
};

class text : public Printable {
public:
    virtual ~text() = default;
    virtual std::string printAsText() const = 0;
};

class JSON : public Printable {
public:
    virtual ~JSON() = default;
    virtual std::string printAsJSON() const = 0;
};

class Data : public HTML, public JSON, public text
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            printAsText();
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            printAsJSON();
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

void saveTo(std::ofstream& file, const Data& data)
{ 
        file << data.printAsText();
}

void saveToAsHTML(std::ofstream& file, const Data& printable) {
    saveTo(file, printable);
}

void saveToAsJSON(std::ofstream& file, const Data& printable) {
    saveTo(file, printable);
}

void saveToAsText(std::ofstream& file, const Data& printable) {
    saveTo(file, printable);
}




int main() {

    Data::Format Text = Data::Format::kText;
    Data data("Text", Text);

    std::ofstream out;
    out.open("file.txt");
    saveToAsText(out, data);

}