#include <gtest/gtest.h>

#include "InvalidStateException.hpp"

#include "Resource.hpp"

#include "ResourceTable.hpp"

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

TEST(ResourceTableTest, constructorTestPrimary) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);

    const ResourceTable table(resArray, size, capacity);
    ASSERT_EQ(table.getCapacity(), capacity);
    ASSERT_EQ(table.getResourceCount(), size);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);

    ASSERT_EQ(table["a"].getConsumption(), 1);
    ASSERT_EQ(table["b"].getConsumption(), 3);
    ASSERT_EQ(table["c"].getConsumption(), 5);

    ASSERT_EQ(table["a"].getProduction(), 2);
    ASSERT_EQ(table["b"].getProduction(), 3);
    ASSERT_EQ(table["c"].getProduction(), 4);

    ASSERT_EQ(table["a"].getPrice(), 3);
    ASSERT_EQ(table["b"].getPrice(), 2);
    ASSERT_EQ(table["c"].getPrice(), 1);

    delete [] resArray;
}

TEST(ResourceTableTest, constructorOther) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);

    const ResourceTable table(resArray, size, capacity);

    const ResourceTable &other(table);

    ASSERT_EQ(other.getCapacity(), capacity);
    ASSERT_EQ(other.getResourceCount(), size);
    ASSERT_EQ(other.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);

    ASSERT_EQ(other["a"].getConsumption(), 1);
    ASSERT_EQ(other["b"].getConsumption(), 3);
    ASSERT_EQ(other["c"].getConsumption(), 5);

    ASSERT_EQ(other["a"].getProduction(), 2);
    ASSERT_EQ(other["b"].getProduction(), 3);
    ASSERT_EQ(other["c"].getProduction(), 4);

    ASSERT_EQ(other["a"].getPrice(), 3);
    ASSERT_EQ(other["b"].getPrice(), 2);
    ASSERT_EQ(other["c"].getPrice(), 1);

    delete [] resArray;
}

TEST(ResourceTableTest, copyEquals) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);

    const ResourceTable table(resArray, size, capacity);

    ResourceTable other;
    other = table;

    ASSERT_EQ(other.getCapacity(), capacity);
    ASSERT_EQ(other.getResourceCount(), size);
    ASSERT_EQ(other.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);

    ASSERT_EQ(other["a"].getConsumption(), 1);
    ASSERT_EQ(other["b"].getConsumption(), 3);
    ASSERT_EQ(other["c"].getConsumption(), 5);

    ASSERT_EQ(other["a"].getProduction(), 2);
    ASSERT_EQ(other["b"].getProduction(), 3);
    ASSERT_EQ(other["c"].getProduction(), 4);

    ASSERT_EQ(other["a"].getPrice(), 3);
    ASSERT_EQ(other["b"].getPrice(), 2);
    ASSERT_EQ(other["c"].getPrice(), 1);

    delete [] resArray;
}

TEST(ResourceTableTest, constructorEmpty) {
    const ResourceTable table;
    ASSERT_EQ(table.getCapacity(), 0);
    ASSERT_EQ(table.getResourceCount(), 0);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_EMPTY);
}

TEST(ResourceTableTest, constructorException) {
    EXPECT_ANY_THROW(ResourceTable(nullptr, 3, 1));
}

TEST(ResourceTableTest, multiplyTest) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ResourceTable table(resArray, size, capacity);

    EXPECT_ANY_THROW(table * -1);

    const auto multiplied = table * 2;

    ASSERT_EQ(multiplied.getCapacity(), capacity);
    ASSERT_EQ(multiplied.getResourceCount(), size);
    ASSERT_EQ(multiplied.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);

    ASSERT_EQ(multiplied["a"].getConsumption(), 2);
    ASSERT_EQ(multiplied["b"].getConsumption(), 6);
    ASSERT_EQ(multiplied["c"].getConsumption(), 10);

    ASSERT_EQ(multiplied["a"].getProduction(), 4);
    ASSERT_EQ(multiplied["b"].getProduction(), 6);
    ASSERT_EQ(multiplied["c"].getProduction(), 8);

    delete [] resArray;
}

TEST(ResourceTableTest, setGetCapacity) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ResourceTable table(resArray, size, capacity);

    EXPECT_ANY_THROW(table.setCapacity(-1));
    EXPECT_ANY_THROW(table.setCapacity(2));
    table.setCapacity(4);
    EXPECT_EQ(table.getCapacity(), 4);
    table.setCapacity(6);
    EXPECT_EQ(table.getCapacity(), 6);

    delete[] resArray;
}

TEST(ResourceTableTest, moveConstructor) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ResourceTable table(resArray, size, capacity);

    const ResourceTable other(std::move(table));

    ASSERT_EQ(other.getCapacity(), capacity);
    ASSERT_EQ(other.getResourceCount(), size);
    ASSERT_EQ(other.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);
    ASSERT_EQ(table.getCapacity(), 0);
    ASSERT_EQ(table.getResourceCount(), 0);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_EMPTY);
    ASSERT_EQ(other["a"].getConsumption(), 1);
    ASSERT_EQ(other["b"].getConsumption(), 3);
    ASSERT_EQ(other["c"].getConsumption(), 5);
    delete [] resArray;
}

TEST(ResourceTableTest, moveEquals) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ResourceTable table(resArray, size, capacity);

    ResourceTable other;
    other = std::move(table);

    ASSERT_EQ(other.getCapacity(), capacity);
    ASSERT_EQ(other.getResourceCount(), size);
    ASSERT_EQ(other.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);
    ASSERT_EQ(table.getCapacity(), 0);
    ASSERT_EQ(table.getResourceCount(), 0);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_EMPTY);
    ASSERT_EQ(other["a"].getConsumption(), 1);
    ASSERT_EQ(other["b"].getConsumption(), 3);
    ASSERT_EQ(other["c"].getConsumption(), 5);
    delete [] resArray;
}

TEST(ResourceTableTest, rename) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    const ResourceTable table(resArray, size, capacity);
    table.renameResourceByName("a", "d");
    ASSERT_EQ(table.getResourceCount(), 3);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);
    EXPECT_ANY_THROW(table["a"]);
    ASSERT_EQ(table["d"].getConsumption(), 1);
    ASSERT_EQ(table["d"].getProduction(), 2);
    ASSERT_EQ(table["d"].getPrice(), 3);

    table.renameResourceByName("d", "d");
    ASSERT_EQ(table["d"].getConsumption(), 1);
    ASSERT_EQ(table["d"].getProduction(), 2);
    ASSERT_EQ(table["d"].getPrice(), 3);
    delete [] resArray;
}

TEST(ResourceTableTest, profit) {
    constexpr int size = 3;
    constexpr int capacity = 5;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    const ResourceTable table(resArray, size, capacity);

    double c = 0;
    EXPECT_ANY_THROW(c = table.countAllProfit(-1));
    ASSERT_EQ(c, 0);
    ASSERT_EQ(table.countAllProfit(0), 0);
    constexpr int days = 3;
    ASSERT_EQ(table.countAllProfit(days),
              resArray[0].calculateProfit(days) + resArray[1].calculateProfit(days) + resArray[2].calculateProfit(days)
    );

    delete [] resArray;
}

TEST(ResourceTableTest, getStatus) {
    constexpr int size = 3;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ASSERT_EQ(ResourceTable(resArray, size, size).getStatus(), ResourceTable::FILL_STATUS::STATUS_FULL);
    ASSERT_EQ(ResourceTable(nullptr, 0, 5).getStatus(), ResourceTable::FILL_STATUS::STATUS_EMPTY);
    ASSERT_EQ(ResourceTable(resArray, size, size + 2).getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);

    delete [] resArray;
}

TEST(ResourceTableTest, deleteFromTable) {
    constexpr int size = 3;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ResourceTable table(resArray, size, size);
    EXPECT_ANY_THROW(table.deleteFromTable("x"));
    const Resource r = table.deleteFromTable("b");
    ASSERT_EQ(table.getResourceCount(), 2);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);
    ASSERT_EQ(table.getCapacity(), 3);
    ASSERT_EQ(r.getConsumption(), 3);
    ASSERT_EQ(r.getProduction(), 3);
    ASSERT_EQ(r.getPrice(), 2);

    ResourceTable other;
    EXPECT_ANY_THROW(other.deleteFromTable("a"));
    delete [] resArray;
}

TEST(ResourceTableTest, testPlusAssign) {
    constexpr int size = 3;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    ResourceTable table(resArray, size, size);
    const auto r = Resource("x", 2, 3, 4);
    EXPECT_ANY_THROW(table += r);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_FULL);
    table.setCapacity(4);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED);
    EXPECT_ANY_THROW(table["x"]);
    table += r;
    ASSERT_EQ(table["x"].getConsumption(), 2);
    ASSERT_EQ(table["x"].getProduction(), 3);
    ASSERT_EQ(table["x"].getPrice(), 4);
    ASSERT_EQ(table.getStatus(), ResourceTable::FILL_STATUS::STATUS_FULL);
    delete [] resArray;
}

TEST(ResourceTableTest, toString) {
    constexpr int size = 3;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    const ResourceTable table(resArray, size, size);
    ASSERT_EQ(table.toString(),
              "ResourceTable(3, 3)\n\t" + resArray[0].toString()
              + "\n\t" + resArray[1].toString()
              + "\n\t" + resArray[2].toString()
    );

    delete [] resArray;
}

TEST(ResourceTableTest, outputStreamTable) {
    constexpr int size = 3;
    auto *resArray = new Resource[size];
    resArray[0] = Resource("a", 1, 2, 3);
    resArray[1] = Resource("b", 3, 3, 2);
    resArray[2] = Resource("c", 5, 4, 1);
    const ResourceTable table(resArray, size, size);
    std::ostringstream os;
    os << table;
    ASSERT_EQ(os.str(), table.toString());
    delete [] resArray;
}

TEST(ResourceTableTest, inputStreamTable) {
    std::istringstream is("1 a 2 3 4");
    ResourceTable res;
    is >> res;
    ASSERT_EQ(res.getCapacity(), 1);
    ASSERT_EQ(res.getResourceCount(), 1);
    ASSERT_EQ(res.getStatus(), ResourceTable::FILL_STATUS::STATUS_FULL);
    ASSERT_EQ(res["a"].getConsumption(), 2);
    ASSERT_EQ(res["a"].getProduction(), 3);
    ASSERT_EQ(res["a"].getPrice(), 4);
}

int main(int argc, char * *argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
