#include <jni.h>
#include <string>


typedef struct Matrix
{
    jint width;
    jint height;
    jfloat *elements;
} Matrix;


void Init(float *data, int size)
{
    for (int i = 0; i < size; ++i)
    {
        data[i] = i;
    }
}


void matrix_multiplication_on_cpu(Matrix C, Matrix A, Matrix B)
{
    for (int row = 0; row < A.height; ++row)
    {
        for (int col = 0; col < B.width; ++col)
        {
            float x = 0.0f;
            for (int p = 0; p < A.width; ++p)
            {
                x += A.elements[row * A.width + p] * B.elements[p * B.width + col];
            }
            C.elements[row * C.width + col] = x;
            x = 0;
        }
    }
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication0124_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapplication0124_MainActivity_countup(
        JNIEnv *env,
        jobject obj,
        jint value) {
    return value + 1;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapplication0124_MainActivity_countdown(
        JNIEnv *env,
        jobject obj,
        jint value) {
    return value - 1 ;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapplication0124_MainActivity_matrix(
        JNIEnv *env,
        jobject obj,
        jfloat value) {

    /*行列のサイズ定義*/
    Matrix hA, hB, hC;
    hA.height = hC.height = 1;
    hA.width = hB.height = 1320;
    hB.width = hC.width = 2048;

    /*ホストメモリの確保*/
    unsigned int A_size_byte = sizeof(jfloat) * hA.height * hA.width;
    unsigned int B_size_byte = sizeof(jfloat) * hB.height * hB.width;
    unsigned int C_size_byte = sizeof(jfloat) * hC.height * hC.width;
    hA.elements = (jfloat *)malloc(A_size_byte);
    hB.elements = (jfloat *)malloc(B_size_byte);
    hC.elements = (jfloat *)malloc(C_size_byte);

    /*配列に行列の入力値を代入*/
    Init(hA.elements, hA.height * hA.width);
    Init(hB.elements, hB.height * hB.width);

    for(int i=0; i<8; i++) {
        matrix_multiplication_on_cpu(hC, hA, hB);
    }

    return hC.elements[10];
}