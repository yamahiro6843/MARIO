#pragma once 

#include "ProjecterUtils.h"

namespace Projecter 
{
	class DispImage : public Image
	{
	public:
		DispImage()
		{}

		void DisplayToWindow()
		{
			// �v���W�F�N�^�ɓ��e
			cvNot( this->spImage.get() , this->spImage.get() ) ;
			cvShowImage( "Projecter Image" , this->spImage.get() ) ;
//			cvWaitKey(3);
		}

	};

}
