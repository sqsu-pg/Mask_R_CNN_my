/*
 * @Author: your name
 * @Date: 2021-11-02 19:04:17
 * @LastEditTime: 2021-11-03 14:29:43
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
    PyObject* py_def = NULL;
    PyObject* py_add = NULL;

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
    std::cout << "加载函数..." << std::endl;
    py_def = PyObject_GetAttrString(py_module, "ver1");
    PyObject* py_def2 = PyObject_GetAttrString(py_module, "hello");
    py_add = PyObject_GetAttrString(py_module, "add");
    PyObject* py_getstr = PyObject_GetAttrString(py_module, "get_str");
    //py_def = PyDict_GetItemString(py_Dict, "ver1");

    std::cout << "运行函数..." << std::endl;

    PyObject_CallObject(py_def2, NULL);
    //? 不需要参数输入的函数，用上面的进行调用最好，这个有问题PyObject_CallFunction(py_def2, " ");

    PyObject* py_args2 = Py_BuildValue("(ii)", 28, 102);
    PyObject* py_ret2 = PyObject_CallObject(py_add, py_args2);

    int res = 0;
    PyArg_Parse(py_ret2, "i", &res);
    std::cout << "求和为: " << res << std::endl;

    std::cout << "使用元组(tuple)进行传参" << std::endl;
    PyObject* py_args3 = NULL;
    py_args3 = PyTuple_New(2);
    PyTuple_SetItem(py_args3, 0, Py_BuildValue("s", "paul "));
    PyTuple_SetItem(py_args3, 1, Py_BuildValue("s", "george "));

    PyObject* py_ret3 = PyObject_CallObject(py_getstr, py_args3);
    char* ret_str1;
    int ret_str2, ret_str3;
    PyArg_ParseTuple(py_ret3, "s|i|i", &ret_str1, &ret_str2, &ret_str3);//todo ? 返回多个字符串时没有高清楚，返回int没啥问题
    std::cout << " get str 函数: " << ret_str1 << " " << ret_str2 << ret_str3 << std::endl;


    

    PyObject* py_args = Py_BuildValue("(s)", "pg");

    //? PyObject* py_ret = PyObject_CallFunction(py_def, "s", "pg");
    PyObject* py_ret = PyObject_CallObject(py_def, py_args);

    std::cout << "获取python函数返回值..." << std::endl;
    char* py_version;
    PyArg_Parse(py_ret, "s", &py_version);
    std::cout << py_version << std::endl;


    //doing 释放
    Py_DECREF(py_module);
    //Py_DECREF(py_Dict);
    Py_DECREF(py_add);
    Py_DECREF(py_getstr);
    Py_DECREF(py_args2);
    Py_DECREF(py_ret2);
    Py_DECREF(py_def);
    Py_DECREF(py_def2);
    Py_DECREF(py_ret);
    Py_DECREF(py_args);
    Py_DECREF(py_args3);
    Py_DECREF(py_ret3);
    Py_Finalize();//doing 关闭python功能

    return 0;
}