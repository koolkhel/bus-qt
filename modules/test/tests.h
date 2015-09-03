#ifndef TESTS_H
#define TESTS_H
#include <QMap>
#include <QString>
#include <QDebug>

//TODO
#define COMPARE(condition1, condition2) \
    if((condition1) != (condition2)) { int *i = NULL; *i = 5; } qDebug()

#define ASSERT_TRUE(condition) COMPARE(condition, true)
#define ASSERT_FALSE(condition) COMPARE(condition, false)
#define ASSERT_EQ(condition1, condition2) COMPARE(condition1, condition2)
#define ASSERT_GE(condition1, condition2) COMPARE(((condition1) >= (condition2)), true)
#define ASSERT_GR(condition1, condition2) COMPARE(((condition1) >   (condition2)), true)
#define ASSERT_LE (condition1, condition2) COMPARE(((condition1) <= (condition2)), true)
#define ASSERT_LW(condition1, condition2) COMPARE(((condition1) <   (condition2)), true)

class DrawTest {
protected:
    static QMap < QString, QMap < QString, DrawTest *> >  * pointers;
};

QMap < QString, QMap < QString, DrawTest *> > *DrawTest::pointers =new  QMap < QString, QMap < QString, DrawTest *> >();

#define TEST_CLASS_NAME_(test_case_name, test_name) \
  test_case_name##_##test_name##_Test

#define DISALLOW_COPY_AND_ASSIGN_(type)\
private: \
    type(type const &);\
    void operator=(type const &)

# define TEST(test_case_name, test_name)\
class TEST_CLASS_NAME_(test_case_name, test_name) : public DrawTest {\
 public:\
  TEST_CLASS_NAME_(test_case_name, test_name)() { \
    (*pointers)["" #test_case_name""]["" #test_name ""] = this;qDebug() << "wow";\
}\
    DISALLOW_COPY_AND_ASSIGN_(\
        TEST_CLASS_NAME_(test_case_name, test_name));\
 public:\
  virtual void TestBody();\
};\
static TEST_CLASS_NAME_(test_case_name, test_name) * \
    ptr_##test_case_name##_##test_name = new TEST_CLASS_NAME_(test_case_name, test_name)();\
void TEST_CLASS_NAME_(test_case_name, test_name)::TestBody()

#endif // TESTS_H

