/*
 * @Author: your name
 * @Date: 2021-11-04 14:47:55
 * @LastEditTime: 2021-11-08 13:31:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Mask_RCNN/samples/C++_API/src/get_mask.cpp
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

using namespace std;


/* int main(int argc, char**argv)
{
    string png_path = "";
    cv::Mat seg = cv::imread(png_path, CV_LOAD_IMAGE_UNCHANGED);

    if (seg.empty())
    {

    }

    return 0;
}


#include "Python.h"
#include "numpy/arrayobject.h"
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std; */
// for the references to all the functions
PyObject *m_PyDict, *m_PyFooBar;

// for the reference to the Pyhton module
PyObject* m_PyModule;

int main() {

  Py_Initialize();
//  PySys_SetArgv(argc, (wchar_t**)argv);
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('./')");
  PyObject *sys_path = PySys_GetObject("path");
  PyList_Append(sys_path, PyUnicode_FromString("."));

  // this macro is defined be NumPy and must be included
  //todo 这个或者下面那个　import_array1(-1);
  import_array();

  m_PyModule = PyImport_ImportModule("cal");

  if (m_PyModule != NULL)
  {
    // get dictionary of available items in the module
    m_PyDict = PyModule_GetDict(m_PyModule);

    // grab the functions we are interested in
    m_PyFooBar = PyDict_GetItemString(m_PyDict, "foo_bar");

    // execute the function
    if (m_PyFooBar != NULL)
    {
      // take a cv::Mat object from somewhere (we'll just create one)
//      cv::Mat img = cv::Mat::zeros(480, 640, CV_8UC3);
        cout << "读入图片" << endl;
        cv::Mat img = cv::imread("/home/george/Mask_RCNN/samples/city-3258896.jpg");
        int r = img.rows;
        int c = img.cols;
        int chnl = img.channels();
        // total number of elements (here it's an RGB image of size 640x480)
        int nElem = r * c * chnl;

        // create an array of apropriate datatype
        uchar* m = new uchar[nElem];

        // copy the data from the cv::Mat object into the array
        std::memcpy(m, img.data, nElem * sizeof(uchar));

        // the dimensions of the matrix
        npy_intp mdim[] = { r, c, chnl};

        // convert the cv::Mat to numpy.array
        PyObject* mat = PyArray_SimpleNewFromData(chnl, mdim, NPY_UINT8, (void*) m);

        // create a Python-tuple of arguments for the function call
        // "()" means "tuple". "O" means "object"
        PyObject* args = Py_BuildValue("(O)", mat);

        // execute the function
        PyArrayObject* ret_img;
        PyObject* result = PyEval_CallObject(m_PyFooBar, args);

        // process the result
        // ...
        cout << "从返回值中解析图片结果: ..." << endl;
        PyArray_OutputConverter(result, &ret_img);
        npy_intp* shape = PyArray_SHAPE(ret_img);
        cout << "返回的numpy的shape为: " << shape[0] << " " << shape[1] << " " << shape[2] << endl;
        cv::Mat images = cv::Mat(shape[0], shape[1], CV_8UC3, PyArray_DATA(ret_img));
        cv::imwrite("c.jpg", images);

        // decrement the object references
        Py_XDECREF(mat);
        Py_XDECREF(result);
        Py_XDECREF(args);
        Py_DECREF(ret_img);

        delete[] m;
    }
  }
  else
  {
    std::cerr << "Failed to load the Python module!" << std::endl;
    PyErr_Print();
  }

  return 0;
}