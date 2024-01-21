#include "skewer.h"

int main() {
    skewer s1, s2;
    string a = "afakj4325";
    string b = "afakj4325";
    s1.createSkewer(a);
    s2.createSkewer(b);
    cout << s1.compareSkewer(s2);
}
