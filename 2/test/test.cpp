#include <gtest/gtest.h>

#include "InvalidStateException.hpp"

#include "Resource.hpp"

TEST(ResourceTests, emptyConstructor) {
    const Resource res;
    ASSERT_EQ(res.getName(), "undefined");
    ASSERT_EQ(res.getPrice(), 0);
    ASSERT_EQ(res.getConsumption(), 0);
    ASSERT_EQ(res.getProduction(), 0);
}

TEST(ResourceTests, fullConstructor) {
    const Resource res("a", 1, 2, 3);
    ASSERT_EQ(res.getName(), "a");
    ASSERT_EQ(res.getConsumption(), 1);
    ASSERT_EQ(res.getProduction(), 2);
    ASSERT_EQ(res.getPrice(), 3);
}

TEST(ResourceTests, gettersSetters) {
    Resource res("a", 1, 2, 3);
    ASSERT_EQ(res.getName(), "a");
    ASSERT_EQ(res.getConsumption(), 1);
    ASSERT_EQ(res.getProduction(), 2);
    ASSERT_EQ(res.getPrice(), 3);
    res.setName("b");
    ASSERT_EQ(res.getName(), "b");
    res.setConsumption(3);
    ASSERT_EQ(res.getConsumption(), 3);
    res.setProduction(4);
    ASSERT_EQ(res.getProduction(), 4);
    res.setPrice(5);
    ASSERT_EQ(res.getPrice(), 5);
}

TEST(ResourceTests, equalsOperator) {
    const Resource res("a", 1, 2, 3);
    Resource res2("b", 3, 2, 1);
    res2 = res;
    ASSERT_EQ(res2.getName(), "a");
    ASSERT_EQ(res2.getConsumption(), 1);
    ASSERT_EQ(res2.getProduction(), 2);
    ASSERT_EQ(res2.getPrice(), 3);
}

TEST(ResourceTest, outputStream) {
    const Resource res("a", 1, 2, 3);
    std::ostringstream os;
    os << res;
    ASSERT_EQ(os.str(), "Resource(a, 1.000000, 2.000000, 3.000000)");
}

TEST(ResourceTest, inputStream) {
    std::istringstream is("b 4 5 6");
    Resource res;
    is >> res;
    ASSERT_EQ(res.getName(), "b");
    ASSERT_EQ(res.getConsumption(), 4);
    ASSERT_EQ(res.getProduction(), 5);
    ASSERT_EQ(res.getPrice(), 6);
}

TEST(ResourceTest, specialConstructor) {
    const Resource res("a", 10);
    ASSERT_EQ(res.getName(), "a");
    ASSERT_EQ(res.getPrice(), 10);
}

TEST(ResourceTest, plusOperator) {
    const Resource a("a", 1, 3, 3);
    const Resource b("b", 3, 2, 1);
    const Resource c = a + b;
    ASSERT_EQ(c.getName(), "ab");
    ASSERT_EQ(c.getConsumption(), 4);
    ASSERT_EQ(c.getProduction(), 5);
    ASSERT_EQ(c.getPrice(), 1);
}

TEST(ResourceTest, lessGreaterOperator) {
    const Resource a("a", 1, 3, 3);
    const Resource b("b", 3, 2, 1);
    const Resource c("c", 3, 2, 1);
    const bool b1 = a < b;
    const bool b2 = b < a;
    const bool b3 = c < a;
    const bool b4 = c < b;
    ASSERT_EQ(a < b, b1);
    ASSERT_EQ(b < a, b2);
    ASSERT_EQ(c < a, b3);
    ASSERT_EQ(c < b, b4);
}

TEST(ResourceTest, exceptions) {
    ASSERT_ANY_THROW(Resource("a",-1, 0, 0));
    ASSERT_ANY_THROW(Resource("a",0, -1, 0));
    ASSERT_ANY_THROW(Resource("a",0, 0, -1));
    Resource res;
    ASSERT_ANY_THROW(res.setPrice(-1));
    ASSERT_ANY_THROW(res.setConsumption(-1));
    ASSERT_ANY_THROW(res.setProduction(-1));
}

TEST(ResourceTest, getProfile) {
    Resource res;
    ASSERT_EQ(res.calculateProfit(0), 0);
    ASSERT_EQ(res.calculateProfit(1), 0);
    ASSERT_EQ(res.calculateProfit(100), 0);

    res.setProduction(100);
    res.setConsumption(50);
    res.setPrice(2);
    ASSERT_EQ(res.calculateProfit(1), 100);
    ASSERT_EQ(res.calculateProfit(2), 200);

    res.setProduction(100);
    res.setConsumption(150);
    ASSERT_EQ(res.calculateProfit(1), -100);
    ASSERT_EQ(res.calculateProfit(2), -200);
    const Resource c = Resource("a", 1, 2, 3) + Resource("b", 3, 3, 1);
    ASSERT_EQ(c.calculateProfit(1), 1);
}

TEST(ResourceTest, multiplyOperator) {
    Resource res("a", 1, 2, 3);
    res = res * 2;
    ASSERT_EQ(res.getName(), "a");
    ASSERT_EQ(res.getConsumption(), 2);
    ASSERT_EQ(res.getProduction(), 4);
    ASSERT_EQ(res.getPrice(), 3);
}

TEST(ResourceTest, exceptionMultiplyOperator) {
    const Resource res("a", 1, 2, 3);
    ASSERT_ANY_THROW(res * -2);
}

TEST(InvalidStateExceptionTest, test) {
    const InvalidStateException e("msg", "field");
    ASSERT_EQ(e.getMessage(), "field: msg");
}

int main(int argc, char * *argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
