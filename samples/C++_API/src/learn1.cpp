/*
 * @Author: your name
 * @Date: 2021-11-02 20:10:20
 * @LastEditTime: 2021-11-02 20:18:17
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Mask_RCNN/samples/C++_API/src/learn1.cpp
 */
#include <Python.h>
#include <iostream>
#include <string>
 
 int main(void) {
     Py_Initialize(); // 启动虚拟机
     if (!Py_IsInitialized())
         return -1;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
     // 导入模块
     PyObject* pModule = PyImport_ImportModule("testpy");
     if (!pModule) {
         printf("Cant open python file!/n");
         return -1;
     }
     // 模块的字典列表
     PyObject* pDict = PyModule_GetDict(pModule);
     if (!pDict) {
         printf("Cant find dictionary./n");
         return -1;
     }
     // 演示函数调用
     PyObject* pFunHi = PyDict_GetItemString(pDict, "sayhi");
     PyObject_CallFunction(pFunHi, "s", "lhb");
     Py_DECREF(pFunHi);
     /* // 演示构造一个Python对象，并调用Class的方法
     // 获取Second类
     PyObject* pClassSecond = PyDict_GetItemString(pDict, "Second");
     if (!pClassSecond) {
         printf("Cant find second class./n");
         return -1;
     }
     //获取Person类
     PyObject* pClassPerson = PyDict_GetItemString(pDict, "Person");
     if (!pClassPerson) {
         printf("Cant find person class./n");
         return -1;
     }
     //构造Second的实例
     PyObject* pInstanceSecond = PyInstance_New(pClassSecond, NULL, NULL);
     if (!pInstanceSecond) {
         printf("Cant create second instance./n");
         return -1;
     }
     //构造Person的实例
     PyObject* pInstancePerson = PyInstance_New(pClassPerson, NULL, NULL);
     if (!pInstancePerson) {
         printf("Cant find person instance./n");
         return -1;
     }
     //把person实例传入second的invoke方法
     PyObject_CallMethod(pInstanceSecond, "invoke", "O", pInstancePerson); */
     //释放
     /* Py_DECREF(pInstanceSecond);
     Py_DECREF(pInstancePerson);
     Py_DECREF(pClassSecond);
     Py_DECREF(pClassPerson); */
     Py_DECREF(pDict);
     Py_DECREF(pModule);
     Py_Finalize(); // 关闭虚拟机
     return 0;
 }