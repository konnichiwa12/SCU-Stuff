//Tree.h
//


template <class X>
class Node{
	private:
		X value;
		X* left;
		X* right;
	public:
		Node(X anObject){
			this.value = anObject;
		}				
		bool member(X anObject){
			if (anObject < this.value){
				if (this.left = NULL){
					return false;
				}
				else{
					return member(anObject);
