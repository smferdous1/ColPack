/*******************************************************************************
    This file is part of ColPack, which is under its License protection.
    You should have received a copy of the License. If not, see 
    <https://github.com/CSCsw/ColPack>
*******************************************************************************/

using namespace std;

#ifndef GRAPHCORE_H
#define GRAPHCORE_H
namespace ColPack
{
	/** @ingroup group1
	 *  @brief class GraphCore in @link group1@endlink.

	 Base class for Graph. Define a Graph: vertices, edges and values (edge's weight - optional); and its statisitcs: max, min and average degree.
	 */

  //user-defined types
  using  SIZE_T = unsigned int;
  //Change this to float/double if the weight of the graph is real  
  using VAL_T = float;
  //The summation type
  using SUM_T = double;
  //Change this to long if number of nodes does not fit into integer
  using  NODE_T = long long;

  //Change this to long if number of edges does not fit into integer
  //typedef  unsigned int EDGE_T;
  using  EDGE_T = long long;
	class GraphCore
	{
	public: //DOCUMENTED

		///Print all the Distance-1 neighbors of VertexIndex (0-based), except the excludedVertex
		void PrintVertexD1Neighbor(NODE_T VertexIndex, NODE_T excludedVertex = -1);
		void GetD1Neighbor(NODE_T VertexIndex, vector<NODE_T> &D1Neighbor, NODE_T excludedVertex = -1);

		/// Print all the Distance-2 neighbors of VertexIndex
		void PrintVertexD2Neighbor(NODE_T VertexIndex);

		/// Check and see if VertexIndex1 and VertexIndex2 are Distance-2 neighbor
		/** Algorithm:
		- Get the set D1_of_VertexIndex1 of all the Distance-1 neighbors of VertexIndex1
		- Get the set D1_of_VertexIndex2 of all the Distance-1 neighbors of VertexIndex2
		- Intersect D1_of_VertexIndex1 and D1_of_VertexIndex2 to see which vertices VertexIndex1 and VertexIndex2 have in common. The result is stored in Intersect_set
		- If the size of Intersect_set > 0 => VertexIndex1 and VertexIndex2 are Distance-2 neighbor
		*/
		bool AreD2Neighbor(NODE_T VertexIndex1, NODE_T VertexIndex2);

		bool operator==(const GraphCore &other) const;
		bool areEqual(const GraphCore &other, bool structureOnly = 1) const;

	protected:

		NODE_T m_i_MaximumVertexDegree;
		NODE_T m_i_MinimumVertexDegree;

		double m_d_AverageVertexDegree;

		string m_s_InputFile;

		vector<EDGE_T> m_vi_Vertices;

		vector<NODE_T> m_vi_Edges;

		vector<VAL_T> m_vd_Values; //!< Edge's weight

		/** m_mimi2_VertexEdgeMap is a matrix that has all the non-zero (edge) in the
		upper triangle marked from 0 to (total number of non-zeros - 1)
		Populated by GraphColoring::AcyclicColoring()
		*/
		map< int, map< int, int> > m_mimi2_VertexEdgeMap; //moved from int GraphColoring::AcyclicColoring()

		/** m_ds_DisjointSets holds a set of bi-color trees
		Populated by GraphColoring::AcyclicColoring()
		*/
		DisjointSets m_ds_DisjointSets; //moved from int GraphColoring::AcyclicColoring()
	public:

		virtual ~GraphCore() {}

		virtual void Clear();

		NODE_T GetVertexCount();

		EDGE_T GetEdgeCount();

		NODE_T GetMaximumVertexDegree();

		NODE_T GetMinimumVertexDegree();

		double GetAverageVertexDegree();

		string GetInputFile();

		void GetVertices(vector<EDGE_T> &output) const;
		vector <EDGE_T>* GetVerticesPtr(){ return &m_vi_Vertices; }

		void GetEdges(vector<NODE_T> &output) const;
		vector <NODE_T>* GetEdgesPtr(){ return &m_vi_Edges; }

		void GetValues(vector<VAL_T> &output) const;

		void GetVertexEdgeMap(map< int, map< int, int> > &output);

		void GetDisjointSets(DisjointSets &output);


	};
}
#endif

