#pragma once
/**
*  @file
*		vis_face_inpainter.h
*
*  @author
*		yangsong
*  @brief
*		Face inpainting based on dictionary
*
*  @details
*		For better recognition
*
*  @date
*		first bulid in Sep. 25th, 2017
*		first update in Oct. 20th, 2017, add "vis_init_facePoints" function
*
*  @version 1.0
*/
#ifndef VIS_FACE_INPAINTER_H_
#define VIS_FACE_INPAINTER_H_

#ifdef VIS_FACE_INPAINTER_EXPORTS
#define VIS_FACE_INPAINTER_API __declspec(dllexport)
#else
#define VIS_FACE_INPAINTER_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include "imageinterface.h"


#define DICT_IMAGE_HEIGHT 211 // the height of dict image
#define DICT_IMAGE_WIDTH 208  // the width of dict image
#define KEY_POINT_NUM 88   //the number of key points

using namespace std;
using namespace cv;

typedef void* MatHandle;//vector<Mat>*

// �������
enum VisFaceInpainterErrorCode
{
	ErrorFaceInpainterOriImageFileLoad = 2,    //����ԭʼͼ��
	ErrorFaceInpainterMaskImageFileLoad,       //����Mask
	ErrorFaceInpainterKeyPointsLoad,               //��������������
	ErrorFaceInpainterMatToBuffer,               //�㷨��󣬽��޸����Mat��ʽͼ��תΪbuffer
};

// ��Ԫ�޸�����ߴ������ѡ��
enum class PatchSizeType
{
	AutoPatchSize = 0,   //�����Զ��жϳߴ�
	BigPatchSize,
	SmallPatchSize
};

/************************************************************************/
/* ����������ƽ���� */
/**
*  @fn vis_face_inpainter
*
*  @brief �̵�
*
*  @details
*		���������������88����
*
*  @param[in]	faceRect	������������
*  @param[in out]    pt88   ���ƽ�����ϵ�88����

*  @return		����ֵ
*  @retval 1	��ʾ�����ɹ�������ֵΪ������ο�VisFaceInpainterErrorCode
*
*/
/************************************************************************/
VIS_FACE_INPAINTER_API bool vis_init_facePoints(const dvRect & faceRect, const string& ref_model_filename, vector<dvPoint2D32f> & pt88);

/************************************************************************/
/* �����ֵ估ģ������  */
/**
*  @fn vis_load_dictionary
*
*  @brief ��������
*
*  @details
*		������Ӧ���ļ�·��������������ݵĽ��
*
*  @param[in]	ref_dict_filename		�ֵ����ݵ��ļ�·��
*  @param[in]	ref_model_filename		ģ�����ݵ��ļ�·��
*  @param[in out]	dict		�洢�ֵ����ݵı���
*  @param[in out]	ref_landmarks		�洢ģ�����ݵı���
*
*  @return		����ֵ
*  @retval true	��ʾ�����ɹ������������ļ�·��
*
*/
/************************************************************************/
VIS_FACE_INPAINTER_API bool vis_load_dictionary(const string& ref_dict_filename, const string& ref_model_filename, MatHandle& dict, vector<dvPoint>& ref_landmarks);

/************************************************************************/
/* �����ֵ估ģ������ */
/**
*  @fn vis_free_dictionary
*
*  @brief ��������
*
*  @details
*		����洢�ֵ估ģ�͵ı�����������л���
*
*  @param[in]	dict		�洢�ֵ����ݵı���
*  @param[in]	ref_landmarks		�洢ģ�����ݵı���
*
*  @return		��
*
*/
/************************************************************************/
VIS_FACE_INPAINTER_API void vis_free_dictionary(MatHandle &dict, vector<dvPoint> &ref_landmarks);

/************************************************************************/
/* �����޸����� */
/**
*  @fn vis_face_inpainter
*
*  @brief �����޸�
*
*  @details
*		���������޸��������ݣ�������յ��޸����
*
*  @param[in]	pSrcImgOri		    ����ԭͼ���buffer
*  @param[in]	pSrcImgMask		����ԭͼ��Mask��buffer
*  @param[in]	ref_landmarks		����ģ������
*  @param[in]	in_landmarks		    ����ԭͼ�����������������
*  @param[in]   dict	                        �����ֵ�����
*  @param[in]   patch_size	            ���뵥Ԫ�޸�����ߴ�
*  @param[in out]    pDstCdvImageInterface   ����޸���ͼ���buffer
*  @param[in out]	pTotal		                              ����ܽ���
*  @param[in out]	pCur		                              �����ǰ����
*
*  @return		����ֵ
*  @retval 1	��ʾ�����ɹ�������ֵΪ������ο�VisFaceInpainterErrorCode
*
*
*  �޸ļ�¼��
*         Oct. 12th, 2017    �����������patch_size���û�������ָ����Ԫ�޸�����Ĵ�С
*
*/
/************************************************************************/
VIS_FACE_INPAINTER_API int vis_face_inpainter(CdvImageInterface* pSrcImgOri, CdvImageInterface* pSrcImgMask, const vector<dvPoint>& ref_landmarks, const vector<dvPoint2D64f>& in_landmarks, const MatHandle& dict, const PatchSizeType& patch_size_type, CdvImageInterface* pDstCdvImageInterface, int* pTotal, int* pCur);





#endif // !VIS_FACE_INPAINTER_H_