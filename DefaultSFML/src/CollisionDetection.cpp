#include "CollisionDetection.h"

bool CollisionDetection::operator()(RectangleShape A, RectangleShape B)
{


	FloatRect FA = A.getGlobalBounds();
	FloatRect FB = B.getGlobalBounds();

	if (FA.intersects(FB))return true;
	else return false;

	//Collision detection variables
	Vector2f obb1LocalPoints[4];
	Vector2f obb2LocalPoints[4];
	Vector2f obb1Normals[4];
	Vector2f obb2Normals[4];

	bool testAxis[4];

	// find center of each rectangle
	Vector2f obb1Center = A.getPosition() + (A.getSize() / 2.0f);
	Vector2f obb2Center = B.getPosition() + (B.getSize() / 2.0f);

	///find the extents of each rectangle
	Vector2f obb1Extent = (A.getSize() / 2.0f);
	Vector2f obb2Extent = (B.getSize() / 2.0f);

	//create local position of each of the verticies
	obb1LocalPoints[0] = Vector2f(obb1Center.x + obb1Extent.x, obb1Center.y + obb1Extent.y);
	obb1LocalPoints[1] = Vector2f(obb1Center.x + obb1Extent.x, obb1Center.y + -obb1Extent.y);
	obb1LocalPoints[2] = Vector2f(obb1Center.x + -obb1Extent.x, obb1Center.y + obb1Extent.y);
	obb1LocalPoints[3] = Vector2f(obb1Center.x + -obb1Extent.x, obb1Center.y + -obb1Extent.y);

	//create local position of each of the verticies
	obb2LocalPoints[0] = Vector2f(obb2Center.x + obb2Extent.x, obb2Center.y + obb2Extent.y);
	obb2LocalPoints[1] = Vector2f(obb2Center.x + obb2Extent.x, obb2Center.y + -obb2Extent.y);
	obb2LocalPoints[2] = Vector2f(obb2Center.x + -obb2Extent.x, obb2Center.y + obb2Extent.y);
	obb2LocalPoints[3] = Vector2f(obb2Center.x + -obb2Extent.x, obb2Center.y + -obb2Extent.y);

	//find rotation matrix
	float vdRotationMatrix1[2][2];
	float vdRotationMatrix2[2][2];

	vdRotationMatrix1[0][0] = cos(A.getRotation()* (3.14 / 180));
	vdRotationMatrix1[0][1] = sin(A.getRotation()* (3.14 / 180));
	vdRotationMatrix1[1][0] = -sin(A.getRotation()* (3.14 / 180));
	vdRotationMatrix1[1][1] = cos(A.getRotation()* (3.14 / 180));

	vdRotationMatrix2[0][0] = cos(B.getRotation()* (180 / 3.14));
	vdRotationMatrix2[0][1] = sin(B.getRotation()* (180 / 3.14));
	vdRotationMatrix2[1][0] = -sin(B.getRotation() * (180 / 3.14));
	vdRotationMatrix2[1][1] = cos(B.getRotation() * (180 / 3.14));

	//translate local coords by rotation matrix
	obb1LocalPoints[0] = Vector2f(obb1LocalPoints[0].x * vdRotationMatrix1[0][0] + obb1LocalPoints[0].x * vdRotationMatrix1[0][1],
		obb1LocalPoints[0].y * vdRotationMatrix1[1][0] + obb1LocalPoints[0].y * vdRotationMatrix1[1][1]
	);
	obb1LocalPoints[1] = Vector2f(obb1LocalPoints[1].x * vdRotationMatrix1[0][0] + obb1LocalPoints[1].x * vdRotationMatrix1[0][1],
		obb1LocalPoints[1].y * vdRotationMatrix1[1][0] + obb1LocalPoints[1].y * vdRotationMatrix1[1][1]
	);
	obb1LocalPoints[2] = Vector2f(obb1LocalPoints[2].x * vdRotationMatrix1[0][0] + obb1LocalPoints[2].x * vdRotationMatrix1[0][1],
		obb1LocalPoints[2].y * vdRotationMatrix1[1][0] + obb1LocalPoints[2].y * vdRotationMatrix1[1][1]
	);
	obb1LocalPoints[3] = Vector2f(obb1LocalPoints[3].x * vdRotationMatrix1[0][0] + obb1LocalPoints[3].x * vdRotationMatrix1[0][1],
		obb1LocalPoints[3].y * vdRotationMatrix1[1][0] + obb1LocalPoints[3].y * vdRotationMatrix1[1][1]
	);

	obb2LocalPoints[0] = Vector2f(obb2LocalPoints[0].x * vdRotationMatrix2[0][0] + obb2LocalPoints[0].x * vdRotationMatrix2[0][1],
		obb2LocalPoints[0].y * vdRotationMatrix2[1][0] + obb2LocalPoints[0].y * vdRotationMatrix2[1][1]
	);
	obb2LocalPoints[1] = Vector2f(obb2LocalPoints[1].x * vdRotationMatrix2[0][0] + obb2LocalPoints[1].x * vdRotationMatrix2[0][1],
		obb2LocalPoints[1].y * vdRotationMatrix2[1][0] + obb2LocalPoints[1].y * vdRotationMatrix2[1][1]
	);
	obb2LocalPoints[2] = Vector2f(obb2LocalPoints[2].x * vdRotationMatrix2[0][0] + obb2LocalPoints[2].x * vdRotationMatrix2[0][1],
		obb2LocalPoints[2].y * vdRotationMatrix2[1][0] + obb2LocalPoints[2].y * vdRotationMatrix2[1][1]
	);
	obb2LocalPoints[3] = Vector2f(obb2LocalPoints[3].x * vdRotationMatrix2[0][0] + obb2LocalPoints[3].x * vdRotationMatrix2[0][1],
		obb2LocalPoints[3].y * vdRotationMatrix2[1][0] + obb2LocalPoints[3].y * vdRotationMatrix2[1][1]
	);

	//find the normals
	obb1Normals[0] = Vector2f(0, 1);
	obb1Normals[1] = Vector2f(1, 0);
	obb1Normals[2] = Vector2f(0, -1);
	obb1Normals[3] = Vector2f(-1, 0);

	//multiply these normals by rotation matrix
	obb1Normals[0] = Vector2f(obb1Normals[0].x * vdRotationMatrix1[0][0] + obb1Normals[0].x * vdRotationMatrix1[0][1],
		obb1Normals[0].y * vdRotationMatrix1[1][0] + obb1Normals[0].y * vdRotationMatrix1[1][1]
	);
	obb1Normals[1] = Vector2f(obb1Normals[1].x * vdRotationMatrix1[0][0] + obb1Normals[1].x * vdRotationMatrix1[0][1],
		obb1Normals[1].y * vdRotationMatrix1[1][0] + obb1Normals[1].y * vdRotationMatrix1[1][1]
	);

	obb1Normals[2] = Vector2f(obb1Normals[2].x * vdRotationMatrix1[0][0] + obb1Normals[2].x * vdRotationMatrix1[0][1],
		obb1Normals[2].y * vdRotationMatrix1[1][0] + obb1Normals[2].y * vdRotationMatrix1[1][1]
	);
	obb1Normals[3] = Vector2f(obb1Normals[3].x * vdRotationMatrix1[0][0] + obb1Normals[3].x * vdRotationMatrix1[0][1],
		obb1Normals[3].y * vdRotationMatrix1[1][0] + obb1Normals[3].y * vdRotationMatrix1[1][1]
	);

	//find the normals
	obb2Normals[0] = Vector2f(0, 1);
	obb2Normals[1] = Vector2f(1, 0);
	obb2Normals[2] = Vector2f(0, -1);
	obb2Normals[3] = Vector2f(-1, 0);

	//multiply these normals by rotation matrix
	obb2Normals[0] = Vector2f(obb2Normals[0].x * vdRotationMatrix2[0][0] + obb2Normals[0].x * vdRotationMatrix2[0][1],
		obb2Normals[0].y * vdRotationMatrix2[1][0] + obb2Normals[0].y * vdRotationMatrix2[1][1]
	);
	obb2Normals[1] = Vector2f(obb2Normals[1].x * vdRotationMatrix1[0][0] + obb2Normals[1].x * vdRotationMatrix2[0][1],
		obb2Normals[1].y * vdRotationMatrix2[1][0] + obb2Normals[1].y * vdRotationMatrix2[1][1]
	);

	obb2Normals[2] = Vector2f(obb2Normals[2].x * vdRotationMatrix2[0][0] + obb2Normals[2].x * vdRotationMatrix2[0][1],
		obb2Normals[2].y * vdRotationMatrix2[1][0] + obb2Normals[2].y * vdRotationMatrix2[1][1]
	);
	obb2Normals[3] = Vector2f(obb2Normals[3].x * vdRotationMatrix2[0][0] + obb2Normals[3].x * vdRotationMatrix2[0][1],
		obb2Normals[3].y * vdRotationMatrix2[1][0] + obb2Normals[3].y * vdRotationMatrix2[1][1]
	);


	//edge counter
	int iEdgesTouching = 0; // allow one edge to touch (for snapping)

	//project each point onto each axis

	for (int axisTestNum = 0; axisTestNum < 4; axisTestNum++)
	{
		//values used for holding min , max
		float OBB1Min = 9999999999;
		float OBB1Max = -9999999999;
		float OBB2Min = 9999999999;
		float OBB2Max = -9999999999;

		// check each vertex on box 1 to get min and max
		for (int vertexNum = 0; vertexNum < 4; vertexNum++)
		{
			// dot product to project this point onto our axis
			float fDotProduct = ((obb1Normals[axisTestNum].x * obb1LocalPoints[vertexNum].x) + (obb1Normals[axisTestNum].y * obb1LocalPoints[vertexNum].y));
			if (fDotProduct < OBB1Min)
			{
				OBB1Min = fDotProduct;
			}
			if (fDotProduct > OBB1Max)
			{
				OBB1Max = fDotProduct;
			}

		}

		// check each vertex on box 2 to get min and max
		for (int vertexNum = 0; vertexNum < 4; vertexNum++)
		{
			float fDotProduct = ((obb2Normals[axisTestNum].x * obb2LocalPoints[vertexNum].x) + (obb2Normals[axisTestNum].y * obb2LocalPoints[vertexNum].y));
			if (fDotProduct < OBB2Min)
			{
				OBB2Min = fDotProduct;
			}
			if (fDotProduct > OBB2Max)
			{
				OBB2Max = fDotProduct;
			}

		}
		//alow one edge
		if (OBB2Min == OBB1Max || OBB2Min == OBB1Min || OBB2Max == OBB1Min || OBB2Max == OBB1Max)
		{
			iEdgesTouching++;
		}

		//check each box min and max for over lap
		if (OBB2Min <= OBB1Max && OBB2Min >= OBB1Min)
		{
			testAxis[axisTestNum] = true; // There is a collision along this axis
			
		}
		else if (OBB2Max >= OBB1Min && OBB2Max <= OBB1Max)
		{
			testAxis[axisTestNum] = true; // There is a collision along this axis
			
		}
		else
		{
			testAxis[axisTestNum] = false; // There is no collision along this axis
			return false;

		}
	}


	//there was a collision
	if (iEdgesTouching == 4) return false;
	
	return true;
	

}


