#include "Drink.h"

using namespace std;
namespace seneca {
ostream& Drink::print(ostream& ostr) const {
    ostr << left << setw(28) << setfill('.') << (m_size ? m_name : "Unnamed Drink");
    ostr << " ";
    if (m_size == 'S')
        ostr << "SML..";
    else if (m_size == 'M')
        ostr << "MID..";
    else if (m_size == 'L')
        ostr << "LRG..";
    else if (m_size == 'X')
        ostr << "XLR..";
    else
        ostr << ".....";
    ostr << " " << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price() << endl;
    return ostr;
}

bool Drink::order() {
    cout << "Drink Size Selection\n"
         << "   1- Small\n"
         << "   2- Medium\n"
         << "   3- Large\n"
         << "   4- Extra Large\n"
         << "   0- Back\n> ";
    int selection;
    cin >> selection;
    switch (selection) {
        case 1:
            m_size = 'S';
            break;
        case 2:
            m_size = 'M';
            break;
        case 3:
            m_size = 'L';
            break;
        case 4:
            m_size = 'X';
            break;
        default:
            m_size = '\0';
            break;
    }
    return m_size != '\0';
}

ifstream& Drink::read(ifstream& file) {
    char name[256];
    double price;
    if (file.getline(name, 256, ',') && file >> price) {
        file.ignore();
        this->name(name);
        this->price(price);
        m_size = '\0';
    }
    return file;
}

double Drink::price(double price) {
    // re-evaluate following statement
    Billable::price(price);

    if (m_size == 'S') return Billable::price() / 2.0;
    if (m_size == 'M') return Billable::price() * 0.75;
    if (m_size == 'X') return Billable::price() * 1.5;
    return Billable::price();
}

double Drink::price() const {
    if (m_size == 'S') return Billable::price() / 2.0;
    if (m_size == 'M') return Billable::price() * 0.75;
    if (m_size == 'X') return Billable::price() * 1.5;
    return Billable::price();
}
}  // namespace seneca