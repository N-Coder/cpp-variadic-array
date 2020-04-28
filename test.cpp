#include "ExampleClass.h"
#include "Array.h"
#include "helper.h"
#include <memory>

int main() {
    ArrayWithCopiedDefault<int> test1(5, 11);
    test1[2] = 12;
    std::cout << test1 << std::endl;
    test1.m_default = std::make_tuple<int>(21);
    test1.initialize_with_default();
    std::cout << test1 << std::endl;

    ArrayWithDefault<std::tuple<int, bool>> test2(5);
    std::cout << test2 << std::endl;

    Array<std::tuple<int, bool>> test3(5, 11, false);
    std::cout << test3 << std::endl;

    ArrayWithCopiedDefault<std::tuple<int, bool>> test4(5, std::make_tuple(22, true));
    std::cout << test4 << std::endl;

    Array<std::unique_ptr<std::string>> test5(5);
    test5[2] = std::make_unique<std::string>("hello world");
    std::cout << test5 << std::endl;

    std::cout << "test with ExampleClass<is_copy_constructible, is_default_constructible>" << std::endl;

    ArrayWithDefault<ExampleClass<false, false>, int> FF_expl_const(2, 11);
    //ArrayWithDefault<ExampleClass<false, false>> FF_default_const(2);
    //ArrayWithCopiedDefault<ExampleClass<false, false>> FF_copy_const(2, ExampleClass<false, false>(11));

    ArrayWithDefault<ExampleClass<true, false>, int> TF_expl_const(2, 22);
    //ArrayWithDefault<ExampleClass<true, false>> TF_default_const(2);
    ArrayWithCopiedDefault<ExampleClass<true, false>> TF_copy_const(2, ExampleClass<true, false>(22));

    ArrayWithDefault<ExampleClass<false, true>, int> FT_expl_const(2, 33);
    ArrayWithDefault<ExampleClass<false, true>> FT_default_const(2);
    //ArrayWithCopiedDefault<ExampleClass<false,true>> FT_copy_const(2, ExampleClass<false,true>(33));

    ArrayWithDefault<ExampleClass<true, true>, int> TT_expl_const(2, 44);
    ArrayWithDefault<ExampleClass<true, true>> TT_default_const(2);
    ArrayWithCopiedDefault<ExampleClass<true, true>> TT_copy_const(2, ExampleClass<true, true>(44));

}