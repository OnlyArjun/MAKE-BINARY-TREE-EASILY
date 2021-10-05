#include <iostream>
#include <string>

using namespace std;
int user_choices;	string user_inputs;

//a template which will be used further for creation of nodes of our binary tree
template<typename my_btree>
class btree_nodes{
	public:
		my_btree data; btree_nodes* left;	btree_nodes* right;
		
		btree_nodes(){
			left=NULL; right=NULL;	
		}
		btree_nodes(my_btree val){
			data=val; left=NULL; right=NULL;	
		}
};

//  Please add / modify your own favorite traversal here and have a btree_nodes<type>* as its parameter
/* void my_favorite_traversal(btree_nodes<type>* root){
	if(root==NULL){ cout<<"NULL\n"; return;	}
	
	cout<<root->data<<"\n";
	my_favorite_traversal(root->left);
	my_favorite_traversal(root->right);
}
*/


// a void function used for tree expansion using the preorder and inorder given by the user
void pre_and_in(btree_nodes<char>* curr_root, string left_subtree, string right_subtree, string preorder){
	//if both the left and right subtree are empty i.e. it's the leaf node
	if(left_subtree.empty()==true && right_subtree.empty()==true){ return; }
	
	// if the left subtree is not empty
	if(left_subtree.empty()==false){
		
		//we will find the root from it using the preoder given 
		//and then break the existing left subtree into its child left and right subtree
		string cpy1="", cpy2="";	int new_root_idx=-1;
		for(int i=1;i<preorder.size();i++){
			for(int j=0;j<left_subtree.size();j++){
				if(preorder[i]==left_subtree[j]){ new_root_idx=j; break; }
			}
			if(new_root_idx!=-1){ break; }
		}
		curr_root->left=new btree_nodes<char>(left_subtree[new_root_idx]);

		for(int i=0;i<new_root_idx;i++){ cpy1+=left_subtree[i]; }
		for(int i=new_root_idx+1;i<left_subtree.size();i++){ cpy2+=left_subtree[i]; }

		pre_and_in(curr_root->left,cpy1,cpy2,preorder);
	}

	if(right_subtree.empty()==false){
		
		//we will find the root from it using the preoder given 
		//and then break the existing right subtree into its child left and right subtree
		string cpy3="", cpy4="";	int new_root_idx=-1;
		for(int i=1;i<preorder.size();i++){
			for(int j=0;j<right_subtree.size();j++){
				if(preorder[i]==right_subtree[j]){ new_root_idx=j; break; }
			}
			if(new_root_idx!=-1){ break; }
		}
		curr_root->right=new btree_nodes<char>(right_subtree[new_root_idx]);

		for(int i=0;i<new_root_idx;i++){ cpy3+=right_subtree[i]; }
		for(int i=new_root_idx+1;i<right_subtree.size();i++){ cpy4+=right_subtree[i]; }

		pre_and_in(curr_root->right,cpy3,cpy4,preorder);
	}

	return;
}

//similar implementation as the above pre_and_in 
//just changed the traversal of the order other than the inorder 
//we will traverse from the end in the postorder as it goes like LEFT --> RIGHT --> ROOT 
//hence root can be found easily if we traverse from the back
void post_and_in(btree_nodes<char>* curr_root, string left_subtree, string right_subtree, string postorder){
	if(left_subtree.empty()==true && right_subtree.empty()==true){ return; }
	
	if(left_subtree.empty()==false){
		
		string cpy1="", cpy2="";	int new_root_idx=-1;
		for(int i=postorder.size()-2;i>=0;i--){
			for(int j=0;j<left_subtree.size();j++){
				if(postorder[i]==left_subtree[j]){ new_root_idx=j; break; }
			}
			if(new_root_idx!=-1){ break; }
		}
		curr_root->left=new btree_nodes<char>(left_subtree[new_root_idx]);

		for(int i=0;i<new_root_idx;i++){ cpy1+=left_subtree[i]; }
		for(int i=new_root_idx+1;i<left_subtree.size();i++){ cpy2+=left_subtree[i]; }

		post_and_in(curr_root->left,cpy1,cpy2,postorder);
	}

	if(right_subtree.empty()==false){
		string cpy3="", cpy4="";	int new_root_idx=-1;
		for(int i=postorder.size()-2;i>=0;i--){
			for(int j=0;j<right_subtree.size();j++){
				if(postorder[i]==right_subtree[j]){ new_root_idx=j; break; }
			}
			if(new_root_idx!=-1){ break; }
		}
		curr_root->right=new btree_nodes<char>(right_subtree[new_root_idx]);

		for(int i=0;i<new_root_idx;i++){ cpy3+=right_subtree[i]; }
		for(int i=new_root_idx+1;i<right_subtree.size();i++){ cpy4+=right_subtree[i]; }

		post_and_in(curr_root->right,cpy3,cpy4,postorder);
	}

	return;
}

//a void function used to intialize a root node and 
//take input the in, pre and post order of the tree to make
void make_my_tree(int x){

	string preorder, postorder, inorder;
	if(x==1){
		cout<<"\n\t PLEASE ENTER THE PREORDER OF YOUR TREE :- "; 	cin>>preorder;
		cout<<"\n\t PLEASE ENTER THE INORDER OF YOUR TREE :- "; 	cin>>inorder;

		int i;		//finding the root of the tree in inorder i.e. char same as the first char of the preorder 
		for(i=0;i<inorder.size();i++){ if(inorder[i]==preorder[0]){ break; } }

		string left_subtree="", right_subtree="";		//two strings which contains the right and left subtrees
		for(int j=0;j<i;j++){ left_subtree+=inorder[j]; }
		for(int j=i+1;j<inorder.size();j++){ right_subtree+=inorder[j]; }

		btree_nodes<char>* root=new btree_nodes<char>(preorder[0]);		//making a root node with value as the first char of preorder
		pre_and_in(root,left_subtree,right_subtree,preorder);
		
		cout<<"\n\n\n";
		//my_favorite_traversal(root);		//calling your favorite traversal function
	}	
	else{
		cout<<"\n\t PLEASE ENTER THE POSTORDER OF YOUR TREE :- "; 	cin>>postorder;
		cout<<"\n\t PLEASE ENTER THE INORDER OF YOUR TREE :- "; 	cin>>inorder;

		int i;		//finding the root of the tree in inorder i.e. char same as the last char of the postorder 
		for(i=postorder.size()-2;i>=0;i--){ if(inorder[i]==postorder[postorder.size()-1]){ break; } }

		string left_subtree="", right_subtree="";			//two strings which contains the right and left subtrees
		for(int j=0;j<i;j++){ left_subtree+=inorder[j]; }
		for(int j=i+1;j<inorder.size();j++){ right_subtree+=inorder[j]; }

		btree_nodes<char>* root=new btree_nodes<char>(postorder[postorder.size()-1]);		//making a root node with value as the last char of postorder
		post_and_in(root,left_subtree,right_subtree,postorder);

		cout<<"\n\n\n";
		//my_favorite_traversal(root);	//calling your favorite traversal function
	}
}


int main(){
	
	cout<<"YOU HAVE TO ENTER AMONG THE FOLLOWINGS IN ORDER TO MAKE A TREE PLEASE CHOOSE AMONG THE FOLLOWING :- \n\n";
	cout<<"\t\t1. PREORDER AND INORDER \n";
	cout<<"\t\t2. POSTORDER AND INORDER \n";
	
	//taking the choice of the user
	cout<<"PLEASE ENTER YOUR CHOICE :- "; cin>>user_choices;
	switch(user_choices){
		case 1:{
			make_my_tree(1);	//calling a void function to carry out the further process
			break;
		}
		case 2:{
			make_my_tree(2);	//calling a void function to carry out the further process
			break;
		}
		default:{
			cout<<"\nWRONG OPTION\n";
			break;
		}
	}
	
	return 0; 
}
