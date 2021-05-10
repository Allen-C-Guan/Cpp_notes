
#ifndef CPP_PRIMER_SALE_DATA_H
#define CPP_PRIMER_SALE_DATA_H
namespace cpp_primer {
    class Sale_data {
    public:
        int a;
        Sale_data() = default;
        explicit Sale_data(int a);
    };
    Sale_data operator+ (const Sale_data&, const Sale_data&);
}
#endif //CPP_PRIMER_SALE_DATA_H
