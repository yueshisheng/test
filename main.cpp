#include <iostream>
#include <functional>
#include <memory>
#include<stdio.h>
#include<cctype>
#include <valarray>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <semaphore.h>
#include <unistd.h>
#include<set>

sem_t productsem1,productsem2;


using namespace std;
typedef std::function<int(int)> callfunc;
class person{
public:

    string* str;

    virtual void print(){//函数如果声明为virtual，则在运行的时候会判断类型，否则在编译时就被判断类型
        cout<<"person print"<<endl;
    }
    void work(){
        cout<<"person work"<<endl;
    }
    person(){

    }
    person(string* str){
        this->str=str;

    }
    person(person& p){//深拷贝，其实就是传一个引用进去
        this->str = new string(*(p.str));
        cout<<"deep copy"<<endl;
        cout<<*this->str<<endl;

    }



    ~person(){
        cout<<"finish class"<<endl;
    };
};

class women final{

};


class man:public  person{
public:

    string school="neu";
    void print() override{
        cout<<"man print"<<endl;
    }
    void work() {
        cout<<"man work"<<endl;
    }

};



void programA_FunA1(callfunc cf) {
    printf("I'am ProgramA_FunA1 and be called..\n");
    cf(1);
}

int p3(int a){
    printf("hhhhhh\n");
    return 0;
}
template<class T>
void programA_FunA2(T t) {
    printf("I'am ProgramA_FunA2 and be called..\n");
    cout<<t<<endl;


}

void programB_FunB1(void (*callback1)()) {
    printf("I'am programB_FunB1 and be called..\n");
    callback1();
}

union token{//union好处是比较节省空间
    //默认都是公有的,同一时刻只能有一个值,完成推送
    int age10;
    double age20;

    token() {

    }
    ~token() {

    }
};

template<class T1,class T2,class T3>
 void test1(tuple<T1,T2,T3> t2){
     cout<<get<1>(t2)<<endl;

}

void test3(int a){
    cout<<a<<endl;
}


struct  people{
    alignas(max_align_t) int age;

};




enum class color{
    red=9,
    green,
    white
};//枚举类相较于枚举，可以降低命名空间的污染


int testplace(int a,int b){
    cout<<a+b<<endl;
    return a+b;

}
mutex m;
void proc1(int a)
{

    cout << "proc1函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 2 << endl;


}

void proc2(int a)
{

    cout << "proc2函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 1 << endl;


}


class A{
    int a;
    virtual void print(){};//8个字节，有一个虚函数指针
    char c;
    double d;

};



void test6(string&& string){
    cout<<string<<endl;
}

 class cc{

    public:




     friend void testfr();//friend函数只能在类外部定义
     friend class rr;


     void print3()=delete;//加delete，说明该函数不能被使用
     cc()=default;//默认的构造函数
     cc(int a){
         cout<<a<<endl;
     }
     const int a=100;
    mutable int b=1000;//在const函数中，想修改值，用该关键字修饰,且常函数中，不能调用非常函数
    int print() const{
        cout<<a<<endl;


    }
    void print2() {
        cout<<a<<endl;

        auto func1=[this](int arg4){
            return  a+arg4;
        };


    }
private:
    static int money;//static的变量必须在类外部初始化,但是const static的变量可以在内部初始化


};

class rr{
public:
    void printcc(){
        cout<<cc::money<<endl;//被声明friend类的，可以调用声明类的私有方法

    }
 private:
    int rrage;
};



int cc::money=1000;

void testfr(){
    cout<<cc::money<<endl;//可以访问私有变量
}


void * product(void *){
    while(1){
        sem_wait(&productsem1);
        cout<<"生产了："<<endl;
        sem_post(&productsem2);
    }
}
void * consumer(void *){
    while(1){
        sem_wait(&productsem2);
        cout<<"消费了："<<endl;
        sem_post(&productsem1);
    }
}




class retrangle{
public :
    int length;
    int width;
    retrangle(){

}
    retrangle(int length,int width){
        this->length=length;
        this->width=width;

     }

     retrangle operator-(retrangle& ret1){

        retrangle retrangle2;
        retrangle2.length=retrangle2.length-ret1.length;
        retrangle2.width=this->width-ret1.width;
         return retrangle2;




   }


   bool operator<(retrangle& ret1){
        retrangle retrangle2;
        if(retrangle2.length<ret1.length){
            return true;
        }
        return false;
    }


    friend ostream& operator<<(ostream& os, retrangle& ret1){
        os<<"length:"<<ret1.length<<" width:"<<ret1.width<<endl;
        return os;

    }


};

#include<future>
int testpromise(promise<int>& ref){
    ref.set_value(100);
    this_thread::sleep_for(chrono::seconds(3));
    return 1001;

}


condition_variable cv2;
bool ready=false;

void work(){
    unique_lock<mutex> uniqueLock(m);
    if(ready==false) { //条件不成立，则进入阻塞
        cv2.wait(uniqueLock);
    }
    if(ready==true) {
        cout << "work正在工作" << endl;
    }

    
}

int testdefered(){
    cout<<"同步任务，直到调用get方法才能执行"<<endl;
    return 100;

}
 thread_local int num1=0;
void testlocal(){
    lock_guard<mutex> lockGuard(m);
    num1++;
    cout<<"threadlocal:"<<num1<<endl;
}
volatile bool flag=false; //修改对其他进程是可见的
void print(){
    while(flag==false) {
        cout<<"flag是false"<<endl;
    }
    cout<<"flag是true"<<endl;
}



#include <semaphore.h>
#include <queue>
queue<int> messageQueue;

void messageproducer(){
    for(int i=0;i<10;i++){
        {
            unique_lock<mutex> uniqueLock(m);
            messageQueue.push(i);
            cout<<"把生产者的生产放入消息队列中"<<i<<endl;
        }
        cv2.notify_all();
    }
}


void messageconsumer(){
    while(true){
        {
            unique_lock<mutex> uniqueLock2(m);
            if(messageQueue.empty()){
                cv2.wait(uniqueLock2);
            }
            if(!messageQueue.empty()){
                cout<<"消费者从消息队列中取出："<<messageQueue.front()<<endl;
                messageQueue.pop();
            }
            uniqueLock2.unlock();

        }
        
    }
}
class student{
public:
    typedef string name;
    int age;
    student(string name,int age){
        this->age=age;


    }

};

template<class T>
class teacher{
public:
    string phone;
    typename T::name name="shisheng";
    teacher(T t){
        cout<<name<<endl;

    }
};






void* hello(void *arg){
    cout<<"子进程"<<endl;
    pthread_exit((void *) "hhhh");
}


#include <deque>
#include <map>

bool compare(pair<string,int> a,pair<string,int> b){
    if(a.second<b.second){
        return true;
    }
    return false;

}


class myclass2;
class myclass{
public:
    myclass(){
        cout<<"该类创建"<<endl;
    }
    ~myclass(){
        cout<<"该类被销毁"<<endl;
    }
    shared_ptr<myclass2> my2;
    void setA(shared_ptr<myclass2> s2){
        my2=s2;
    }


};

class myclass2{
public:
    myclass2(){
        cout<<"myclass被创建"<<endl;
    }
    ~myclass2(){
        cout<<"myclass被销毁"<<endl;
    }
    shared_ptr<myclass> s3;
    void setB(shared_ptr<myclass> s4){
        s3=s4;
    }
};



class box{
public:
    int length;
    explicit box(int length){
        this->length=length;

    }
    void getLenth(){
        cout<<"长度是："<<this->length<<endl;
    }
};

enum color1{
    red=10,//不初始化，默认是0,不断递增
    yellow,
    blue
};


#include<stack>


template<class T>
void testtem(T t){
    stack<T> stack1;
    stack1.push(t);
    cout<<stack1.top()<<endl;


}



class fileguard{
    public:
        fileguard(){


        }
        ~fileguard(){
            if(file.is_open()){
                file.close();
            }
            cout<<"文件已经关闭"<<endl;



        }

    private:
        ofstream file;

    };









int main(int argc, char **argv) {












    thread lamadathread([](int num){
        cout<<"通过lamada表达式创建进程："<<num<<endl;
    },100);
    lamadathread.join();








    testtem(1);
    testtem("hh");



    color1 color9=color1::blue;
    cout<<color9<<endl;










    //box box1=10;如果不使用explicit可以使用隐式声明，如果使用explicit，则只能用显示声明
    box box1(10);
    box1.getLenth();





    ofstream ofs;//文件的写模式
    ofs.open("test.txt");
    char data[100];
    cin.getline(data, 100);
    ofs<<data<<endl;
    ifstream ifs;//文件的写模式
    ifs.open("test.txt");
    char data1[100];
    ifs>>data1;
    cout<<data1<<endl;
    ifs.seekg(2);//移动文件指针的位置
    ifs.seekg(2,ios::cur);
    char data3[100];
    ifs>>data3;
    cout<<data3<<endl;











    


    int nums[2][3]={1,2,3,4,5,6};
    int (*ptr4)[3];//把*ptr4理解为指向每一行的指针，这是数组指针
    cout<<*(*(nums+1))<<endl;
    ptr4=&(*(nums+1));
    cout<<(*ptr4)[2]<<endl;














    shared_ptr<myclass> ms2(new myclass);
    shared_ptr<myclass2> ms11(new myclass2);
    ms2->setA(ms11);
    ms11->setB(ms2);

    cout<<ms2.use_count()<<endl;
    cout<<ms11.use_count()<<endl;

    shared_ptr<myclass> ms3(ms2);
    cout<<ms2.use_count()<<endl;


    weak_ptr<myclass> wp(ms3);
    ms2.reset();
    cout<<ms3.use_count()<<endl;
    cout<<(wp.lock())<<endl;












    map<string,int> map2;
    map2.insert(pair<string,int>("shi",2));
    map2.insert(pair<string,int>("sheng",1));
    map2.insert(pair<string,int>("yue",5));
    vector<pair<string,int>> vector1(map2.begin(),map2.end());
    sort(vector1.begin(),vector1.end(), compare);
    map<string,int>::iterator it2;
    for(it2=map2.begin();it2!=map2.end();it2++) {
        cout<<it2->first<<" "<<it2->second<<endl;
    }








      set<int> set1;
      set1.insert(2);
      set1.insert(3);
      set<int> set2;
      set2.swap(set1);
      cout<<*set2.begin()<<endl;
      multiset<int> mset1;//可以有重复
      mset1.insert(2);
      mset1.insert(2);
      cout<<mset1.size()<<endl;
      pair<int,string> pair2(2,"shi");
      pair<string,int> pair3=make_pair("hi",100);
      cout<<pair3.first<<endl;
      cout<<pair3.second<<endl;
      pair<int,string> pair4(2,"shi");
      pair<string,int> pair5=make_pair("hi",100);
      cout<<pair5.first<<endl;
      cout<<pair2.second<<endl;







      int  array1[]={1,2,3,4,5};
      deque<int> deq1(array1,array1+5);
      cout<<*deq1.begin()<<endl;
      deq1.push_back(7);
      deq1.push_front(0);

      cout<<deq1.front()<<endl;
      cout<<deq1.back()<<endl;
      cout<<deq1[3]<<endl;










    student st1("yue",12);
    teacher<student> teacher1(st1);




















     //消息队列
//    thread mth(&messageproducer);
//
//    thread mth2(&messageconsumer);
//    thread mth4(&messageconsumer);
//      mth2.join();
//
//      mth4.join();
//      mth.join();











     thread t6(print);
     this_thread::sleep_for(chrono::seconds(1));
     flag=true;
     t6.join();




    thread thread11(&testlocal);
    thread thread21(&testlocal);
    thread11.join();
    thread21.join();
    


    future<int> fut=async(launch::deferred,&testdefered);//调用get方法才能执行
    cout<<"先开始了"<<endl;
    fut.get();
    



    thread worker(&work);
    this_thread::sleep_for(chrono::seconds(1));
    {
        lock_guard<mutex> lockGuard(m);
        ready=true;
        cv2.notify_one();
        
    }
    worker.join();
    cout<<ready<<endl;




    promise<int> pro1;//通过promise来指定参数
    future<int> fu1 = async(&testpromise, ref(pro1));
    future_status status = fu1.wait_for(chrono::seconds(2));
    try {
        if (status == future_status::ready) {
            cout << "result=" << fu1.get() << endl;
        } else if (status == future_status::timeout) {
            cout << "超时了" << endl;
        }
    }

  catch(const std::future_error& e) {
      cout<<"future_error:"<<e.code()<<e.what()<<endl;
}





    future<int> f=pro1.get_future();
    cout<<f.get()<<endl;
    if(!fu1.valid()){
        cout<<"该future已经无效"<<endl;
    }









    retrangle retrangle1(30,50);
    retrangle retrangle2(29,49);
    retrangle retrangle3;

    cout<<retrangle1;
    

    


    retrangle3=retrangle1-retrangle2;
    cout<<retrangle3.length<<endl;
    bool flag=retrangle1<retrangle2;
    cout<<"res:"<<flag<<endl;











    cout<< sizeof(long double)<<endl;











    sem_init(&productsem1,0,0);
    sem_init(&productsem2,10,0);
//    pthread_t pid1,pid2;
//    pthread_create(&pid1,NULL,product,NULL);
//    pthread_create(&pid2,NULL,consumer,NULL);
//    pthread_join(pid1,NULL);
//    pthread_join(pid2,NULL);





    int i19=120;
    char cs[20];
    string  s1;
    stringstream ss;
    ss<<i19;
    s1=ss.str();
    cout<<s1<<endl;



    //cin>>s1;
    sprintf(cs,"%d",i19);//将数字转换为字符串
    cout<<cs<<endl;
    getline(cin, s1);//能读取空格
    cout<<s1<<endl;//有空格的不能读取






    int num21=10000;
    int num22=10;
    int *const cptr=&num21;//只能指向一个变量的指针，该变量的值可以发生变化



    num21=10;
    cout<<*cptr<<endl;


    const int num1=10;
    const int *ptr1=&num1;
    cout<<*ptr1<<endl;








    rr r1;
    r1.printcc();



    testfr();




    int i1=10;
    int& ref=i1;
    int i2=100;
    ref=i2;
    cout<<ref<<endl;
    cout<<i1<<endl;







   token ut10;
//   ut1.age10=30;
   ut10.age20=20;
   cout<<ut10.age20<<endl;








    int args1=10;
    int args2=20;
    typedef int T;//typedef的用法
    T args3=30;

    auto func=[&args1,&args2](int t){//按引用来捕获值，可直接修改，按值捕获，则不能修改值
        return args1+args2+t;
    };
    int res=func(30);
    cout<<res<<endl;






    const cc cc1;


    cout<<cc1.a<<endl;//const修饰类对象，则该对象只能访问const类型的变量和函数
    cc1.print();




    string s="hello world";
    string& ls=s;
    string &&rs=move(s);//通过move将左值引用转换为右值引用
    cout<<rs<<endl;

    test6(forward<string>(rs));//还保持右值引用
    test6(move(s));




    string str1="hello";
    string* str2= nullptr;
    str2=&str1;

    person p1(str2);
    person p4(p1);


    cout<< sizeof(A)<<endl;//是8的整数倍，计算class的大小








    int* intptr= nullptr;
    intptr=new int[2]{2,5};//new是用一个指针来接收的，指向连续几个变量
    cout<<*(intptr+1)<<endl;
    delete intptr;
    cout<<*intptr<<endl;



    thread thread1(proc1,2);

    thread thread2(proc2,2);

    thread1.join();
    thread2.join();






    unordered_map<int,string> unmap={
            {2,"a"},
            {3,"b"},
            {1,"c"}
    };
    for(auto i:unmap){
        cout<<i.first<<" "<<i.second<<endl;
    }




    std::function<int(int)> foo=std::bind(testplace,std::placeholders::_1,2);
    foo(3);



    color color1=color::green;
    cout<<static_cast<int>(color1)<<endl;//枚举类在使用的时候必须强转换



    cout<< alignof(people)<<endl;

 //QUICK SORT

    bool num4=true;

    cout<< sizeof(num4)<<endl;

    vector<int> v1;

    v1.reserve(100);
    cout<<v1.capacity()<<endl;
    v1.resize(200);
    cout<<v1.capacity()<<endl;//size即为实际的元素个数




     const int num2=20;
    int &&a2 =30;//右值引用
     const int& c1=num2;//num2为const，则该引用必须为const
    const int& c3=100;
    cout<<c1<<endl;
    a2=move(c1);//move可以将左值引用，转换为右值引用
    cout<<"move的使用"<<a2<<endl;

    a2=11;
    cout<<a2<<endl;





    decltype(1+2) e1;//可以根据表达式推断出值的类型
    cout<<typeid(e1).name()<<endl;//输出类型






    function<void(int)> f1=test3;
    f1(111);




     tuple<int,string,int> t= make_tuple(1,"2",3);
     test1(t);











    string str;
    getline(cin,str);
    cout<<(char)toupper(str[0])<<endl;



    int* ptr3=0;//代表该指针没有指向任何值































   shared_ptr<string> st= make_shared<string>(3,'9');
   shared_ptr<string> st2(st);
   cout<<*st<<endl;
   cout<<st2.use_count()<<endl;
   shared_ptr<string> st3= make_shared<string>("hh");
   cout<<st3.use_count()<<endl;
   st3=st2;
   cout<<st3.use_count()<<endl;


   unique_ptr<int> ut(new int(100));
   unique_ptr<int> ut2(ut.release());
   cout<<*ut2<<endl;
   unique_ptr<int> ut3= move(ut2);
   cout<<*ut3<<endl;









    programA_FunA1(&p3);
    programA_FunA2("hhhhh");
}
