#include <gtest/gtest.h>

#include "Car.hpp"

#include "TestValidator.hpp"

#include "CarTomlValidator.hpp"

#include "CarSerializer.hpp"

#include <algorithm>

TEST(ModelTests, shouldGetSetWork) {
    Car car("brand", "owner", 10.0);
    ASSERT_EQ(car.getBrand(), "brand");
    ASSERT_EQ(car.getOwner(), "owner");
    ASSERT_DOUBLE_EQ(car.getMileage(), 10.0);
    car.setBrand("b");
    car.setOwner("o");
    car.setMileage(0.0);
    ASSERT_EQ(car.getBrand(), "b");
    ASSERT_EQ(car.getOwner(), "o");
    ASSERT_DOUBLE_EQ(car.getMileage(), 0.0);
}

TEST(ValidatorTests, testValidatorShouldPass) {
    TestValidator v;
    ASSERT_NO_THROW(v.validate("completely wrong"));
}


TEST(ValidatorTests, testCarTomlValidatorGeneral) {
    CarTomlValidator v;
    ASSERT_ANY_THROW(v.validate("completely wrong"));
    ASSERT_NO_THROW(v.validate("[car]\nbrand = \"a\"\nowner = \"b\"\nmileage = 2.5\n"));
}

TEST(ValidatorTests, testCarTomlValidatorStructure) {
    CarTomlValidator v;
    ASSERT_ANY_THROW(v.validate("[car]\nbrand = \"brand\"\nmileage = 100.32\n"));
    ASSERT_NO_THROW(v.validate("[car]\nbrand = \"brand\"\nowner = \"me\"\nmileage = 100.32\n"));
    ASSERT_ANY_THROW(v.validate("[car]\nbrand = \"brand\"\nowner = \"me\""));
}

TEST(ValidatorTests, testCarTomlValidatorBrand) {
    CarTomlValidator v;
    ASSERT_ANY_THROW(v.validate("[car]\nbrand = \"?!Oh-   :(\"\nmileage = 100.32\n"));
    ASSERT_NO_THROW(v.validate("[car]\nbrand = \"Oh-   \"\nowner = \"me\"\nmileage = 100.32\n"));
    ASSERT_ANY_THROW(
        v.validate("[car]\nbrand = \"?!Oh-   :( a"
            " a a a a aa a a a a a a a a a a a a a a a a a a\"\nmileage = 100.32\n"
        ));
}

TEST(ValidatorTests, testCarTomlValidatorOwner) {
    CarTomlValidator v;
    ASSERT_NO_THROW(v.validate("[car]\nbrand = \"Oh   \"\nowner = \"OwnerOwnerOwner\"\nmileage = 100.32\n"));
}

TEST(ValidatorTests, testCarTomlValidatorMileage) {
    CarTomlValidator v;
    ASSERT_NO_THROW(v.validate("[car]\nbrand = \"Oh-   \"\nowner = \"OwnerOwnerOwner\"\nmileage = 100.32\n"));
    ASSERT_ANY_THROW(v.validate("[car]\nbrand = \"Oh-   :(\"\nmileage = 100,32\n"));
    ASSERT_ANY_THROW(v.validate("[car]\nbrand = \"Oh-   :(\"\nmileage = ahahaha\n"));
    ASSERT_ANY_THROW(v.validate("[car]\nbrand = \"Oh-   :(\"\nmileage = 100..323..32\n"));
}

TEST(SerializerTests, testCarSerializerDeserializeToml) {
    CarSerializer c(new CarTomlValidator());
    ASSERT_NO_THROW(c.deserialize("[car]\nbrand = \"Oh-   \"\nowner = \"OwnerOwnerOwner\"\nmileage = 100.32\n"));
    ASSERT_ANY_THROW(c.deserialize("[car]\nbrand = \"Oh-   :(\"\nmileage = 100,32\n"));
}

TEST(SerializerTests, testCarSerializerDeserializeTomlProp) {
    CarSerializer c(new TestValidator());
    const Car car = c.deserialize("[car]\nbrand = \"Oh-   \"\nowner = \"OwnerOwnerOwner\"\nmileage = 100.32\n");
    ASSERT_EQ(car.getBrand(), "Oh-   ");
    ASSERT_EQ(car.getOwner(), "OwnerOwnerOwner");
    ASSERT_DOUBLE_EQ(car.getMileage(), 100.32);
}

TEST(SerializerTests, testCarSerializerSerializerToml) {
    CarSerializer c(new TestValidator());
    const Car car("Brand", "Owner", 10.2);
    const std::string s = c.serialize(car, "new");
    ASSERT_EQ(s, "[new]\nbrand = \"Brand\"\nowner = \"Owner\"\nmileage = 10.2");
}

TEST(SerializerTests, testCarSerializerSerializerOverridesEquals) {
    CarSerializer c(new TestValidator());
    const Car car("Brand", "Owner", 10.2);
    const std::string s = c.serialize(car, "new");
    ASSERT_EQ(s, "[new]\nbrand = \"Brand\"\nowner = \"Owner\"\nmileage = 10.2");

    auto arr = new char[s.size()];
    std::ranges::transform(s, arr, [](const char ch) { return ch; });

    Car c1 = c.deserialize(s);
    Car c2 = c.deserialize(s.c_str());
    Car c3 = c.deserialize(arr, s.size());

    ASSERT_EQ(c1.getBrand(), c2.getBrand());
    ASSERT_EQ(c1.getOwner(), c2.getOwner());
    ASSERT_DOUBLE_EQ(c1.getMileage(), c2.getMileage());
    ASSERT_EQ(c2.getBrand(), c3.getBrand());
    ASSERT_EQ(c2.getOwner(), c3.getOwner());
    ASSERT_DOUBLE_EQ(c2.getMileage(), c3.getMileage());
    delete[] arr;
}


int main(int argc, char * *argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
