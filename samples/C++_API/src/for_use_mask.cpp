/*
 * @Author: your name
 * @Date: 2021-11-08 13:29:37
 * @LastEditTime: 2021-12-10 20:31:24
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /Mask_RCNN/samples/C++_API/src/use_mask_with_pic.cpp
 */
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include <iostream>
#include <fstream>

using namespace std;

size_t init_numpy()
{
    cout << "导入array" << endl;
    import_array();
    cout << "导入array成功" << endl;
}

cv::Mat toMat(const PyObject *o)
{
    cv::Mat m;

    if(!o || o == Py_None)
    {
        cout << "data is null" << endl;
    }


    int typenum = PyArray_TYPE(o);//doing 数据类型
    int type = typenum == NPY_UBYTE ? CV_8U : typenum == NPY_BYTE ? CV_8S :
                                                                    typenum == NPY_USHORT ? CV_16U : typenum == NPY_SHORT ? CV_16S :
                                                                                                                            typenum == NPY_INT || typenum == NPY_LONG ? CV_32S :
                                                                                                                                                                        typenum == NPY_FLOAT ? CV_32F :
                                                                                                                                                                                               typenum == NPY_DOUBLE ? CV_64F : -1;


    int ndims = PyArray_NDIM(o);//doing 维度数目

    int size[CV_MAX_DIM+1];
    size_t step[CV_MAX_DIM+1], elemsize = CV_ELEM_SIZE1(type);
    const npy_intp* _sizes = PyArray_DIMS(o);
    const npy_intp* _strides = PyArray_STRIDES(o);
    bool transposed = false;

    for(int i = 0; i < ndims; i++)
    {
        size[i] = (int)_sizes[i];
        step[i] = (size_t)_strides[i];
    }

    if( ndims == 0 || step[ndims-1] > elemsize ) {
        size[ndims] = 1;
        step[ndims] = elemsize;
        ndims++;
    }

    if( ndims >= 2 && step[0] < step[1] )
    {
        std::swap(size[0], size[1]);
        std::swap(step[0], step[1]);
        transposed = true;
    }

    if( ndims == 3 && size[2] <= CV_CN_MAX && step[1] == elemsize*size[2] )
    {
        ndims--;
        type |= CV_MAKETYPE(0, size[2]);
    }


    m = cv::Mat(ndims, size, type, PyArray_DATA(o), step);

//     if( m.data )
//     {
// #if ( CV_MAJOR_VERSION < 3)
//         m.refcount = refcountFromPyObject(o);
// #else
//         m.u->refcount = *refcountFromPyObject(o);
// #endif
//         m.addref(); // protect the original numpy array from deallocation
//         // (since Mat destructor will decrement the reference counter)
//     };
//     m.allocator = &g_numpyAllocator;

//     if( transposed )
//     {
//         Mat tmp;
//         tmp.allocator = &g_numpyAllocator;
//         transpose(m, tmp);
//         m = tmp;
//     }
    return m;
}

int main()
{
    //doing 初始化python
    Py_Initialize();
    init_numpy();
    //doing 检查初始化是否成功
    if (!Py_IsInitialized())
    {
        cout << "python 初始化失败 " << endl;
        return -1;
    }

    //doing 运行一些简单的python指令
    PyRun_SimpleString("import sys");
    //PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("sys.path.append('/home/george/Mask_RCNN/samples')");
    // PyRun_SimpleString("sys.path.append('/home/george/SLAM/DynaSLAM/src/python')");
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString("."));


    cout << "读入文件...." << endl;
    PyObject* py_Moudle = PyImport_ImportModule("Mask_class");//doing 读入python文件
    // PyObject* py_Moudle = PyImport_ImportModule("MaskRCNN");//doing 读入python文件
    //doing 检验是否读取成功
    if (!py_Moudle)
    {
        //doing 没读取成功
        cout << "can't find Mask_class.py "<< endl;
        return -1;
    }
    cout << "find Mask_class.py " << endl;

    //doing 获取字典
    /* pDict = PyModule_GetDict(py_Moudle);
    //DOING 检查字典是否获取成功
    if (!pDict)
    {
        cout << "获取字典失败 " << endl;
        return -1;
    }
    cout << "成功获取字典" << endl; */

    //doing 获取类
    //pClass = PyDict_GetItemString(pDict, "Mask");
    cout << "获取类 " << endl;
    PyObject* pClass = PyObject_GetAttrString(py_Moudle, "Mask");
    //doing 检查是否有名字为Mask的类
    if (!pClass || !PyCallable_Check(pClass))
    {
        cout << "can't found class Mask " << endl;
        return -1;
    }
    cout << "find class Mask " << endl;

    //doing 调用类的构造函数构造类的实例
    cout << "调用类的构造函数..." << endl;
    PyObject* pInstance = PyObject_CallObject(pClass, nullptr);
    //doing 检查类实例是否构造成功
    if (!pInstance)
    {
        cout << "构造类实例失败 " << endl;
        return -1;
    }

    //doing 构建py参数列表
    PyObject* ArgList = PyTuple_New(2);
    PyTuple_SetItem(ArgList, 0, pInstance);

    PyObject* pFunc = PyObject_GetAttrString(pClass, "GetDynSeg1");

    // PyObject* pFunc = PyObject_GetAttrString(pClass, "get_img");

    
    for (int i = 0; i < 10; i++)
    {
        

        std::string img_path = "/home/george/data_sets/00/image_0/00000";
        img_path = img_path + std::to_string(i) + ".png";
        cout << "图片路径为 : " << img_path << endl;
        //doing 读取图片
        cout << "imread picture ..." << endl;
        // cv::Mat img = cv::imread("/home/george/Mask_RCNN/samples/C++_API/src/000000005037.jpg");
        cv::Mat img = cv::imread(img_path);
        //doing 检查图片是否读入成功
        if (img.empty())
        {
            return -1;
        }

        

        //doing cv::Mat类型转换为指针
        int r = img.rows;
        int c = img.cols;
        int chnl = img.channels();
        //doing 图片的总共数据
        int nELem = r*c*chnl;
        //doing 在堆上分配内存
        uchar* m = new uchar[nELem];
        //doing 从cv::Mat类型中拷贝数据到堆上
        std::memcpy(m, img.data, nELem * sizeof(uchar));

        //doing numpy类型的维度 //!非常重要
        npy_intp mdim[] = {r, c, chnl};
        //doing 构造numpy类型
        PyObject* PyArray = PyArray_SimpleNewFromData(chnl, mdim, NPY_UINT8, (void*)m);

        //doing 设置传入实例函数的参数
        
        PyTuple_SetItem(ArgList, 1, PyArray);

        //?调用类函数
        
        cout << "调用类函数 ..." << endl;

        cout << "返回值 " << endl;
        PyObject* pRet = NULL;
        pRet = PyObject_CallObject(pFunc, ArgList);//? 这是正确方法

         cout << "从返回值中解析图片结果..." << endl;
        PyArrayObject* ret_img;
        PyArray_OutputConverter(pRet, &ret_img);
        npy_intp* shape = PyArray_SHAPE(ret_img);
        cout << "返回的numpy的shape为: "  << shape[0] << " " << shape[1] << endl;

        cv::Mat mask_img = cv::Mat(shape[0], shape[1], CV_8UC3, PyArray_DATA(ret_img));

        cout << "mask_img 的通道数 : " << mask_img.channels() << endl;
        cout << "mask_img 的数据类型为 : " << mask_img.type() << endl;
        // cv::Mat mask_img = toMat(pRet);

        cout << "为了可视化处理mask_img..." << endl;
        // usleep(40000000);
        // fstream file;
        // file.open("/home/george/Mask_RCNN/samples/C++_API/src/mask.txt");
        cout << "mask_img shape are : " << mask_img.rows << " " << mask_img.cols << endl;
        int size_of_point = 0;
        for (int i = 0; i < mask_img.rows; i++)
        {
            for (int j = 0; j < mask_img.cols; j++)
            {
                if (mask_img.at<cv::Vec3b>(i, j)[0] == 255)
                {
                    size_of_point++;
                }
                // int a = mask_img.at<uchar>(i, j);
                // file << a << " ";
            }
            // file << endl;
        }
        // file.close();

        cout << "可视化结果..." << endl;
        cout << "count of mask are : " << size_of_point << endl;
        cv::imwrite("Mask_result.png", mask_img);

        vector<cv::Mat> mv;
        cv::split(mask_img, mv);
        std::string mask_name = "mask_" + std::to_string(i) + ".png";
        cv::imwrite(mask_name, mv[0]);

        //DOING 释放内存
        
        // Py_XDECREF(PyArray);//doing 不用自己释放
        Py_XDECREF(pRet);
        
         delete [] m;

    }
    
    cout << " 1 " << endl;
    Py_XDECREF(py_Moudle);
    cout << " 2 " << endl;
    Py_XDECREF(pClass);
    cout << " 3 " << endl;
    Py_XDECREF(pInstance);
    cout << " 4 " << endl;
    Py_XDECREF(ArgList);
    cout << " 5 " << endl;
    Py_XDECREF(pFunc);
    cout << " 6 " << endl;
    // Py_FinalizeEx();
    cout << " 7 " << endl;
    return 0;
}