
#include "Sale_data.h" // 必须在namespace打开前include，否则就会把include的内容都放在namespace中了
namespace cpp_primer {
    Sale_data::Sale_data(int a) : a(a) {}

    Sale_data operator+ (const Sale_data &lhs, const Sale_data &rhs) {
        return Sale_data(lhs.a + rhs.a);
    }

}
