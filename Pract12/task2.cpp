#include <iostream>
#include "MyString.h"
#include "Vector.hpp"
using namespace std;

class Control {
protected:
    int x;
    int y;
    int w;
    int h;
public:
    Control(int x, int y, int w, int h) : x(x), y(y), h(h), w(w) {}
    virtual void setDataDialog() = 0;
    virtual void changeSize(int h, int w);
    virtual void changeLocation(int x, int y);
    virtual ~Control() = default;
    virtual Control* clone() const = 0;
};

void Control::changeSize(int h, int w) {
    this->h = h;
    this->w = w;
}
void Control::changeLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

class TextBox : public Control {
    MyString text;

public:
    TextBox(int x, int y, int w, int h) : Control(x, y, w, h) {}
    void setDataDialog() override;
    Control* clone() const override;
};

void TextBox::setDataDialog() {
    cin >> text;
}

Control* TextBox::clone() const {
    return new TextBox(*this);
}

class CheckBox : public Control {
    MyString text;
    bool isChecked = 0;
public:
    CheckBox(int x, int y, int w, int h, const MyString& text) : Control(x, y, w, h), text(text) {}
    void setDataDialog() override;
    Control* clone() const override;
};

void CheckBox::setDataDialog() {
    isChecked = !isChecked;
}

Control* CheckBox::clone() const {
    return new CheckBox(*this);
}

class RadioButton : public Control {
    MyVector<MyString> options;
    int chosen = -1;

public:
    RadioButton(int x, int y, int w, int h) : Control(x, y, w, h) {}
    RadioButton(int x, int y, int w, int h, const MyVector<MyString>& options) : 
        Control(x, y, w, h), options(options) {}
    void setDataDialog() override;
    void addOption(MyString&& toAdd);
    Control* clone() const override;
};

void RadioButton::setDataDialog() {
    int choice;
    cin >> choice;
    if (choice >= options.size())
        return;

    chosen = choice;
}

void RadioButton::addOption(MyString&& toAdd) {
    options.push_back(std::move(toAdd));
}

Control* RadioButton::clone() const {
    return new RadioButton(*this);
}

class Form {
    MyVector<Control*> controls;
    int h;
    int w;
public:
    Form(int h, int w) : h(h), w(w) {}
    void addControl(Control* ctr);
    void changeSize(int h, int w);
    void change(size_t index);
    ~Form();
};

void Form::addControl(Control* ctr) {
    controls.push_back(ctr);
}

void Form::changeSize(int h, int w) {
    this->h = h;
    this->w = w;
}

void Form::change(size_t index) {
    if (index >= controls.size())
        return;

    controls[index]->setDataDialog();
}

Form::~Form() {
    for (int i = 0; i < controls.size(); i++) {
        delete controls[i];
    }
}
