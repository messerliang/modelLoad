
#include "Texture.h"
#include "GL_Error.h"

#include "functions.h"

#include <windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

Texture::Texture(const std::string& imgPath, int flip): m_textureId(-1){
    m_imagePath = utf8_to_ansi(imgPath);
    // ��������
    BasicSet();

    // ��ȡͼƬ
    if (ReadImage(flip)) {

        //int len = MultiByteToWideChar(CP_UTF8, 0, imgPath.c_str(), -1, NULL, 0);
        //std::wstring ws(len, L'\0');
        //MultiByteToWideChar(CP_UTF8, 0, imgPath.c_str(), -1, &ws[0], len);

        //// �Ƴ�ĩβ�� null terminator
        //ws.resize(wcslen(ws.c_str()));
        //std::wcout << ws << " read failed\n";
        std::cout << utf8_to_ansi(imgPath) << "read failed\n";
    }
    else {
        std::cout << "success: " << utf8_to_ansi(imgPath) << std::endl;
    }

    // ��������
    GLCall(glGenTextures(1, &m_textureId));

    // ��
    Bind2D();

    // ����ͼ������
    SetImagData2D();



}

Texture::~Texture() {
    if (m_imageData) {
        free(m_imageData);
    }
    
}

void Texture::SetImagData2D() const {
    if (m_imageData) {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else {
        std::cout << "image data is empty\n";
    }
    
    
}

void Texture::Bind2D() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
}
void Texture::UnBind2D() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned int Texture::GetId()const {
    return m_textureId;
}

void Texture::BasicSet() {
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));      // Ϊ������Сʱ�����ò�����ʽΪ�����
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));       // ����Ŵ�ʹ�����Բ���
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    

}


int Texture::ReadImage(int flip) {

    //if(flipY){ stbi_set_flip_vertically_on_load(true); }
    //
    //m_imageData = stbi_load(m_imagePath.c_str(), &m_width, &m_height, &m_channel, 0);
    //if (!m_imageData) {
    //    return -1;
    //}

    // �ص� opencv �� INFO ��ӡ
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    cv::Mat img = cv::imread(m_imagePath);
    if (img.empty()) {
        std::cout <<m_imagePath<< " read image failed��" << std::endl;
        return -1;
    }
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    if (flip >= -1 && flip <=1) {
        cv::flip(img, img, flip);
        std::cout << "flip: " << flip << std::endl;
    }
    size_t sz = img.total() * img.elemSize();
    m_imageData = (unsigned char*)new char[sz];
    std::memcpy(m_imageData, img.data, sz);
    m_width = img.cols;
    m_height = img.rows;
    m_channel = img.channels();

    return 0;
}

