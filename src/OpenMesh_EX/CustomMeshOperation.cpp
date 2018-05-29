#include "Mesh\GUA_OM.h"

OMT::FIter Tri_Mesh::SelectFace(OMT::Vector3d clicked,bool Mode)
{	
	double min = 5;
	FIter nearest=faces_begin();

	bool outOfRange = 1;

	for (auto V_it = vertices_begin(); V_it != vertices_end(); ++V_it)
	{
		OMT::Vector3d a(point(V_it.handle()).data());		
		if ((clicked - a).length() < 1)
		{
			outOfRange = 0;
			break;
		}		
	}

	if (outOfRange) return faces_end();

	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		double length = 0;
		auto fv_it = fv_iter(f_it);

		/*------------------------------------------------------------find Area cross product*/
		OMT::Vector3d temp1(point(fv_it.handle()).data());
		OMT::Vector3d temp2(point((++fv_it).handle()).data());
		OMT::Vector3d temp3(point((++fv_it).handle()).data());
		
		double Area1= 
		((temp1 - clicked) % (temp2- clicked)).length()/2+
		((temp2 - clicked) % (temp3- clicked)).length()/2+
		((temp3-clicked) % (temp1- clicked )).length()/2;
		
		double Area2= ((temp2-temp1) % (temp3-temp1)).length()/2;
		/*----------------------------------------------------------------------------------*/
		
		if (abs(Area1-Area2)<min)
		{
			min = abs(Area1 - Area2);
			nearest=f_it;
		}	
	}

	bool nearby=0;
	for (auto ff_it = ff_iter(nearest.handle()); ff_it; ff_it++)
	{
		if (property(SelectedF, ff_it.handle())==Mode)
			nearby = 1;
	}

	if (nearby||!selectedFaceCount||(selectedFaceCount==n_faces()))
	{
		if (this->property(SelectedF, nearest.handle()) != Mode)
		{
			this->property(SelectedF, nearest.handle()) = Mode;
			if (Mode)selectedFaceCount++;
			if (!Mode)selectedFaceCount--;
		}
	}	

	return nearest;
}

void Tri_Mesh::clearSelected()
{
	selectedFaceCount = 0;
	for (auto f_it = faces_begin(); f_it != faces_end(); f_it++)
	{
		property(SelectedF, f_it.handle()) = 0;	
	}
	selectedFaceCount = 0;
	delete SubMesh;
	SubMesh = NULL;
}

void Tri_Mesh::ReverseSelected()
{	
	selectedFaceCount = 0;
	for (auto f_it = faces_begin(); f_it != faces_end(); f_it++)
	{		
		property(SelectedF, f_it.handle())= !property(SelectedF, f_it.handle());
		if (property(SelectedF, f_it.handle()))
			selectedFaceCount++;
	}
}

void Tri_Mesh::CreateSubMesh()
{	
	if (SubMesh != NULL)
		delete SubMesh;
	SubMesh = new Tri_Mesh;

	if (!selectedFaceCount)
	{
		//std::cout <<"No Face Selected"<<std::endl;
		delete SubMesh;
		SubMesh = NULL;
		return;
	}

	if (selectedFaceCount==n_faces()&&!countBoundry())
	{
		//std::cout << "Don't Select whole Mesh with no boundary" << std::endl;
		delete SubMesh;
		SubMesh = NULL;
		return;
	}

	///*-----------------------------clear*/
	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		if (property(SelectedF, f_it))
		{
			for (auto fv_it = fv_iter(f_it); fv_it; ++fv_it)
			{
				if (property(subVertex, fv_it.handle()).is_valid())
				property(subVertex, fv_it.handle()).reset();
			}
		}
	}
	///*-----------------------------*/
	
	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{	
		if (property(SelectedF, f_it))
		{		
			for (auto fv_it = fv_iter(f_it); fv_it; ++fv_it)
			{
				OMT::Vector3d a(point(fv_it.handle()).data());

				if(!property(subVertex, fv_it.handle()).is_valid())
					property(subVertex, fv_it.handle()) =
					SubMesh->add_vertex(Tri_Mesh::Point(a[0], a[1], a[2]));
			}
		}
	}

	std::vector<Tri_Mesh::VertexHandle>  face_vhandles;
	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{

		if (property(SelectedF, f_it))
		{
			face_vhandles.clear();
			for (auto fv_it = fv_iter(f_it); fv_it; ++fv_it)
			{
				OMT::Vector3d a(point(fv_it.handle()).data());

				face_vhandles.push_back(property(subVertex, fv_it.handle()));
			}
			SubMesh->add_face(face_vhandles);
		}
	}
}

void Tri_Mesh::calcWeight()
{
	if (!countBoundry())return;
	double total = 0;

	for (auto EIter = edges_begin(); EIter != edges_end(); EIter++)
	{
		HalfedgeHandle hehandle;
		EHandle ehandle = EIter.handle();

		if (!is_boundary(ehandle))
		{
			total = 0;
		
			hehandle = halfedge_handle(ehandle, 0);
			hehandle = next_halfedge_handle(hehandle);
			total += 1 / tan(calc_sector_angle(hehandle));

			hehandle = halfedge_handle(ehandle, 1);
			hehandle = next_halfedge_handle(hehandle);

			total += 1 / tan(calc_sector_angle(hehandle));

			property(weight, ehandle) = total;
			//std::cout <<ehandle.idx()<<"->"<<property(weight, ehandle)<<std::endl;
		}
	}

	for (auto v_it = vertices_begin(); v_it != vertices_end(); v_it++)
	{
		if (!is_boundary(v_it.handle()))
		{
			total = 0;
			for (auto VE_it = ve_iter(v_it); VE_it; VE_it++)
			{				
				total += property(weight,VE_it.handle());			
			}
			property(totalWeight, v_it.handle()) = total;
			//std::cout << v_it.handle().idx() << "->" << property(totalWeight, v_it.handle()) << std::endl;
		}		
	}
};

int Tri_Mesh::countBoundry()
{
	int count = 0;
	for (auto v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		if (is_boundary(v_it))
		{
			count++;
		}
	}
	return count;
}

void Tri_Mesh::drawParameterization(double x,double y)
{
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		glBegin(GL_LINE_LOOP);
		for (auto fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			glVertex3d(property(texCorX, fv_it.handle())+x, property(texCorY, fv_it.handle())+y, 0);
		}
		glEnd();
	}
	glPopAttrib();
	glColor3f(1.0, 1.0, 1.0);	
	glEnable(GL_TEXTURE_2D);
}

void Tri_Mesh::parametrization(double ParamScale, double ParamAngle, double ParamX, double ParamY, bool reverse)
{
	/*-----------------------------------------------parameterization boundary vertex*/
	calcWeight();

	int boundaryNumber = countBoundry();
	if (!boundaryNumber)return;
	
	double interval = (2 * 3.1415926) / boundaryNumber;
	if (reverse) interval *= -1;
	double currentAngle = interval + ParamAngle;

	VIter startVertex;
	for (startVertex = vertices_begin(); !is_boundary(startVertex.handle()); startVertex++);
	VVIter currentVertex = vv_iter(startVertex.handle());

	property(texCorX, startVertex.handle()) = cos(currentAngle)*ParamScale + ParamX;
	property(texCorY, startVertex.handle()) = sin(currentAngle)*ParamScale + ParamY;
	currentAngle += interval;

	while (currentVertex.handle() != startVertex.handle())
	{
		glVertex3dv(point(currentVertex.handle()).data());

		property(texCorX, currentVertex.handle())= cos(currentAngle)*ParamScale + ParamX;
		property(texCorY, currentVertex.handle())= sin(currentAngle)*ParamScale+ ParamY;
		currentAngle += interval;

		currentVertex = vv_iter(currentVertex.handle());
	}
	if (n_vertices() == countBoundry())return;

	/*--------------------------------------------------*/
	 double total = 0;
	 std::map<int,int> IDmap;
	for (auto v_it = vertices_begin(); v_it != vertices_end(); v_it++)
	{	
		if (!is_boundary(v_it))
		{
			IDmap.insert(std::pair<int,int>(v_it.handle().idx(),total));
			total++;
		}
	}
	//std::cout <<IDmap.size()<<std::endl;
	
	SparseMatrix<double> A(IDmap.size(), IDmap.size());
	std::vector<VectorXd> B;
	B.resize(2); //B is 2D

	B[0].resize(IDmap.size());
	B[1].resize(IDmap.size());

	for (int i = 0; i < IDmap.size(); i++)
	{
		B[0][i] = B[1][i] = 0;
	}

	int index = 0;
	for (auto v_it = vertices_begin(); v_it != vertices_end(); v_it++)
	{
		if (!is_boundary(v_it))
		{			
			A.insert(index,index)=1.0;

			double w=property(totalWeight, v_it.handle());

			for (auto ve_it = ve_iter(v_it); ve_it; ve_it++)			
			{
				double eW = property(weight, ve_it.handle());

				auto hehandle = halfedge_handle(ve_it.handle(), 0);
								
				if (to_vertex_handle(hehandle) != v_it.handle())
				{
					if (is_boundary(to_vertex_handle(hehandle)))
					{						
						B[0][index]+= eW*property(texCorX, to_vertex_handle(hehandle))/w;
						B[1][index]+= eW*property(texCorY, to_vertex_handle(hehandle))/w;
					}
					else
					{
						A.insert(index, IDmap[to_vertex_handle(hehandle).idx()]) = -(eW / w);
					}
				}
				else
				{
					if (is_boundary(from_vertex_handle(hehandle)))
					{
						B[0][index] += eW*property(texCorX, from_vertex_handle(hehandle)) / w;
						B[1][index] += eW*property(texCorY, from_vertex_handle(hehandle)) / w;
					}
					else
					{
						A.insert(index, IDmap[from_vertex_handle(hehandle).idx()]) = -(eW / w);
					}
				}

			}
			index++;
		}
	}
	A.makeCompressed();
	/*-------------------------------------------------*/

	SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> linearSolver;
	linearSolver.compute(A);

	std::vector<VectorXd> X;
	X.resize(2);

	X[0] = linearSolver.solve(B[0]);
	X[1] = linearSolver.solve(B[1]);

	//std::cout <<X[0]<<X[1]<<std::endl;

	index = 0;
	for (auto v_it = vertices_begin(); v_it != vertices_end(); v_it++)
	{
		if (!is_boundary(v_it))
		{
			property(texCorX, v_it) = X[0][index];
			property(texCorY, v_it) = X[1][index];
			index++;			
		}
	}

}

void Tri_Mesh::BindColor(double r, double g, double b, double a)
{
	if(selectedFaceCount)
	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		if (property(SelectedF, f_it.handle()))
		{
			property(R, f_it.handle()) = r;
			property(G, f_it.handle()) = g;
			property(B, f_it.handle()) = b;
			property(A, f_it.handle()) = a;
			property(texID, f_it.handle()) =0;
		}
	}
}

void Tri_Mesh::BindTexture(int ID)
{
	if (!SubMesh) return;
	for (auto f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		if (property(SelectedF, f_it.handle()))
		{
			property(texID, f_it.handle()) = ID;			

			/*--------------------------------------------------------*/
			auto fv_it = fv_iter(f_it);
							
			property(x1, f_it.handle())=
					SubMesh->property(texCorX, property(subVertex, fv_it.handle()));

			property(y1, f_it.handle())=
					SubMesh->property(texCorY, property(subVertex, fv_it.handle()));

			++fv_it;

			property(x2, f_it.handle()) =
				SubMesh->property(texCorX, property(subVertex, fv_it.handle()));

			property(y2, f_it.handle()) =
				SubMesh->property(texCorY, property(subVertex, fv_it.handle()));

			++fv_it;
			
			property(x3, f_it.handle()) =
				SubMesh->property(texCorX, property(subVertex, fv_it.handle()));

			property(y3, f_it.handle()) =
				SubMesh->property(texCorY, property(subVertex, fv_it.handle()));
			/*--------------------------------------------------------*/

		}
	}
}

void Tri_Mesh::DeleteBoundary()
{
	std::vector<FHandle> tmp;

	for (auto f_it = faces_begin(); f_it != faces_end(); f_it++)
	{
		if(property(SelectedF, f_it.handle()) == 1)
		for (auto ff_it = ff_iter(f_it.handle()); ff_it; ff_it++)
		{
			if (property(SelectedF, ff_it.handle()) != 1)
				if(find(tmp.begin(),tmp.end(),f_it.handle())==tmp.end())
				tmp.push_back(f_it.handle());
		}
	}

	for (auto f : tmp)
	{
		property(SelectedF, f) = 0;
		selectedFaceCount--;
	}
}

void Tri_Mesh::SelectOneRing()
{
	std::vector<FHandle> tmp;

	for (auto f_it = faces_begin(); f_it != faces_end(); f_it++)
	{
		if (property(SelectedF, f_it.handle()) == 1)
		for (auto ff_it = ff_iter(f_it.handle()); ff_it; ff_it++)
		{
			if (property(SelectedF, ff_it.handle()) != 1)
				if (find(tmp.begin(), tmp.end(), ff_it.handle()) == tmp.end())
					tmp.push_back(ff_it.handle());
		}
	}

	for (auto f : tmp)
	{
		property(SelectedF, f) = 1;
		selectedFaceCount++;
	}

}

void Tri_Mesh::output(std::ostream& out)
{
	
	for (auto f = faces_begin(); f != faces_end(); f++)
	{
		out << f.handle().idx() << " "
			<< property(R, f.handle()) << " "
			<< property(G, f.handle()) << " "
			<< property(B, f.handle()) << " "
			<< property(A, f.handle()) << " "
			<< property(texID, f.handle()) << " "
			<< property(x1, f.handle()) << " "
			<< property(y1, f.handle()) << " "
			<<property(x2, f.handle()) << " "
			<<property(y2, f.handle()) << " "
			<< property(x3, f.handle()) << " "
			<< property(y3, f.handle()) << " "
			<< std::endl;
	}

}

void Tri_Mesh::input(std::istream& in)
{	
	for (auto f = faces_begin(); f != faces_end(); f++)
	{
		int tmp ;
		in >> tmp;
		in >> property(R, f.handle())
			>> property(G, f.handle())
			>> property(B, f.handle())
			>> property(A, f.handle())
			>> property(texID, f.handle())
			>> property(x1, f.handle())
			>> property(y1, f.handle())
			>> property(x2, f.handle())
			>> property(y2, f.handle())
			>> property(x3, f.handle())
			>> property(y3, f.handle());
	}

}