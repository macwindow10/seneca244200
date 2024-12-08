#include "Food.h"
using namespace std;
namespace seneca {

ostream& Food::print(ostream& ostr) const {
    ostr << left << setw(28) << setfill('.') << (ordered() ? m_name : m_name);
    // ostr << " ";
    if (ordered())
        ostr << (m_child ? "Child" : "Adult");
    else
        ostr << ".....";
    ostr << "" << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();
    if (m_customize && &ostr == &cout) {
        ostr << " >> " << m_customize;
    }
    ostr << endl;
    return ostr;
}

bool Food::order() {
    cout << "         Food Size Selection\n"
         << "          1- Adult\n"
         << "          2- Child\n"
         << "          0- Back\n";
    std::cout << std::string(9, ' ');
    std::cout << "> ";
    int selection;
    cin >> selection;
    if (selection == 1) {
        m_child = false;
        m_ordered = true;
    } else if (selection == 2) {
        m_child = true;
        m_ordered = true;
    } else {
        m_ordered = false;
        delete[] m_customize;
        m_customize = nullptr;
    }
    if (m_ordered) {
        cout << "Special instructions\n> ";
        cin.ignore();
        string instructions;
        getline(cin, instructions);
        delete[] m_customize;
        if (!instructions.empty()) {
            m_customize = new char[instructions.length() + 1];
            strcpy(m_customize, instructions.c_str());
        } else {
            m_customize = nullptr;
        }
    }
    return m_ordered;
}

ifstream& Food::read(ifstream& file) {
    char name[256];
    double price;
    if (file.getline(name, 256, ',') && file >> price) {
        file.ignore();
        this->name(name);
        this->price(price);
        m_ordered = false;
        m_child = false;
        delete[] m_customize;
        m_customize = nullptr;
    }
    return file;
}

double Food::price(double price) {
    // re-evaluate following statement
    Billable::price(price);
    return m_child ? Billable::price() / 2.0 : Billable::price();
}

double Food::price() const {
    return m_child ? Billable::price() / 2.0 : Billable::price();
}

Food::~Food() {
    delete[] m_customize;
}

Food::Food(const Food& other) : m_customize(nullptr) {
    *this = other;
}

Food& Food::operator=(const Food& other) {
    if (this != &other) {
        Billable::operator=(other);
        m_ordered = other.m_ordered;
        m_child = other.m_child;
        delete[] m_customize;
        if (other.m_customize) {
            m_customize = new char[strlen(other.m_customize) + 1];
            strcpy(m_customize, other.m_customize);
        } else {
            m_customize = nullptr;
        }
    }
    return *this;
}

}  // namespace seneca