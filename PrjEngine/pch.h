
// 미리 컴파일된 헤더 
// 한번만 컴파일 되어 빌드 성능 상승하나 프로젝트 규모가 커지거나 헤더가 꼬여 link error 발생할 수 있음
// 다음에는 pch 사용하지 않고 해보자

#ifndef PCH_H
#define PCH_H

#include "framework.h"
#include "CEngine.h"

#include "CObject.h"
#include "ICollisionObject.h"

#include "CUserInput.h"

#include "CCircle.h"
#include "CAABB.h"

#include "CTransform.h"
#include "CMatrix.h"
#include <math.h>
#include "CVector.h"

#include "d2d1.h"
#pragma comment(lib, "d2d1")

#endif //PCH_H
