/*
 * @Author: your name
 * @Date: 2021-11-02 19:04:17
 * @LastEditTime: 2021-11-03 15:07:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Mask_RCNN/samples/C++_API/src/lab1.cpp
 */
#include <Python.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <cstdio>

int main()
{
    //doing 初始化python 解释器
    Py_Initialize();
    if (Py_IsInitialized())
    {
        std::cout << "python 完成初始化 " << std::endl;
    }
    else 
    {
        return -1;
    }

    PyObject* py_module = NULL;
    //PyObject* py_Dict = NULL;
    PyObject* py_class = NULL;
    PyObject* py_construct = NULL;
    PyObject* py_Instance = NULL;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    std::cout << "加载module ..." << std::endl;
    py_module = PyImport_ImportModule("version");
    assert(py_module != NULL);
    if (!py_module)
    {
        std::cout << "can't open file" << std::endl;
        return -1;
    }
    //std::cout << "加载词典..." << std::endl;
    //py_Dict = PyModule_GetDict(py_module);
    std::cout << "加载类..." << std::endl;
    //doing 获取类
    py_class = PyObject_GetAttrString(py_module, "Person");

    //DOING 构建实例
    //doing 第一种构造实例的方法
    /* std::cout << "获取构造函数 ..." << std::endl;
    py_construct = PyInstanceMethod_New(py_class);
    std::cout << "调用构造函数: ..." << std::endl;
    py_Instance = PyObject_CallObject(py_construct, nullptr); */

    //doing 第二种构建实例的方法
    py_Instance = PyObject_CallObject(py_class, nullptr);


    std::cout << "调用函数: " << std::endl;
    PyObject_CallMethod(py_Instance, "sayHi", nullptr);
    
    

    Py_DECREF(py_module);
    Py_DECREF(py_class);
    //Py_DECREF(py_construct);
    Py_DECREF(py_Instance);

    Py_Finalize();//doing 关闭python功能

    return 0;
}