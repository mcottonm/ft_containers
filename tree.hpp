#include <iostream>

#define BLACK 0
#define RED 1


struct tree_node
{
	struct tree_node* parent;
	struct tree_node* left;
	struct tree_node* right;
	int color;
	int value;
	tree_node(const int& value) 
	{
		parent = NULL;
		left = NULL;
		right = NULL;
		color = RED;
		this->value = value;
	}
};

void insert_case1(tree_node* n);

tree_node* grandp(tree_node* n)
{
	if (n && n->parent)
		return n->parent->parent;
	else
		return NULL;
}

tree_node* uncle(tree_node* n)
{
	tree_node*g = grandp(n);
	if (!g)
		return NULL;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void adopt(tree_node* n, tree_node* pivot)
{
	pivot->parent = n->parent;
	if(n->parent)
	{
		if (n->parent->left == n)
			n->parent->left = pivot;
		else
			n->parent->right = pivot;
	}
}

void rotate_left(tree_node* n)
{
	tree_node* pivot = n->right;

	adopt(n, pivot);

	n->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = n;
	
	n->parent = pivot;
	pivot->left = n;
}

void rotate_right(tree_node* n)
{
	tree_node* pivot = n->right;

	adopt(n, pivot);

	n->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = n;
	
	n->parent = pivot;
	pivot->right = n;
}

// void insert(tree_node** root, int& value, bool (cmp)(int, int))
// {
// 	if (!*root)
// 	{
// 		*root = new tree_node(value);
// 		insert_case1(*root);
// 	}
// 	else if (cmp((*root)->value, value))
// 	{
// 		if (!((*root)->left))
// 		{
// 			tree_node* in = new tree_node(value);
// 			(*root)->left = in;
// 			in->parent = *root;
// 			insert_case1(in);
// 		}
// 		else
// 			insert(&((*root)->left), value, cmp);
// 	}
// 	else
// 	{
// 		if (!((*root)->right))
// 		{
// 			tree_node* in = new tree_node(value);
// 			(*root)->right = in;
// 			in->parent = *root;
// 			insert_case1(in);
// 		}
// 		else
// 			insert(&((*root)->right), value, cmp);
// 	}
// }

void insert(tree_node* root, int& value, bool (cmp)(int, int))
{
	if (cmp((root)->value, value))
	{
		if (!((root)->left))
		{
			tree_node* in = new tree_node(value);
			(root)->left = in;
			in->parent = root;
			insert_case1(in);
		}
		else
			insert(((root)->left), value, cmp);
	}
	else
	{
		if (!((root)->right))
		{
			tree_node* in = new tree_node(value);
			(root)->right = in;
			in->parent = root;
			insert_case1(in);
		}
		else
			insert(((root)->right), value, cmp);
	}
}

void insert_case5(tree_node* n)
{
	tree_node* g = grandp(n);

	n->parent->color = BLACK;
	g->color = RED;
	if (n == n->parent->left && n->parent == g->left)
		rotate_right(g);
	else
		rotate_left(g);
}

void insert_case4(tree_node* n)
{
	tree_node* g = grandp(n);

	if (n == n->parent->right && n->parent == g->left)
	{
		rotate_left(n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == g->right)
	{
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void insert_case3(tree_node* n)
{
	tree_node *u = uncle(n), *g;

	if ((u != NULL) && (u->color == RED)) 
	{
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandp(n);
		g->color = RED;
		insert_case1(g);
	} 
	else 
		insert_case4(n);
}

void insert_case2(tree_node* n)
{
	if (n->parent->color == BLACK)
		return;
	else
		insert_case3(n);
}

void insert_case1(tree_node* n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(n);
}

tree_node* sibling(tree_node* n)
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void replace_node(tree_node* n, tree_node* child)
{
    child->parent = n->parent;
    if (n == n->parent->left) {
        n->parent->left = child;
    } else {
        n->parent->right = child;
    }
}

bool is_leaf(tree_node* n)
{
	return (n->left || n->right);
}

void delete_case6(tree_node *n)
{
	tree_node *s = sibling(n);

	s->color = n->parent->color;
    n->parent->color = BLACK;

	if (n == n->parent->left) {
        s->right->color = BLACK;
		rotate_left(n->parent);
	} else {
		s->left->color = BLACK;
		rotate_right(n->parent);
	}
}

void delete_case5(tree_node *n)
{
	tree_node *s = sibling(n);

	if  (s->color == BLACK) 
	{ 
		if ((n == n->parent->left) &&
		    (s->right->color == BLACK) &&
		    (s->left->color == RED))
		{
			s->color = RED;
			s->left->color = BLACK;
			rotate_right(s);
		} 
		else if ((n == n->parent->right) &&
		           (s->left->color == BLACK) &&
		           (s->right->color == RED)) 
		{
			s->color = RED;
			s->right->color = BLACK;
			rotate_left(s);
		}
	}
	delete_case6(n);
}

void delete_case4(tree_node* n)
{
	tree_node* s = sibling(n);

	if ((n->parent->color == RED) &&
	    (s->color == BLACK) &&
	    (s->left->color == BLACK) &&
	    (s->right->color == BLACK)) {
		s->color = RED;
		n->parent->color = BLACK;
	} else
		delete_case5(n);
}


void delete_case3(tree_node *n)
{
	tree_node *s = sibling(n);

	if ((n->parent->color == BLACK) &&
	    (s->color == BLACK) &&
	    (s->left->color == BLACK) &&
	    (s->right->color == BLACK)) {
		s->color = RED;
		delete_case1(n->parent);
	} else
		delete_case4(n);
}

void delete_case2(tree_node* n)
{
	tree_node *s = sibling(n);

	if (s->color == RED) {
		n->parent->color = RED;
		s->color = BLACK;
		if (n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
	} 
	delete_case3(n);
}


void delete_case1(tree_node* n)
{
	if (n->parent != NULL)
		delete_case2(n);
}

void delete_one_child(tree_node* n)
{
	tree_node *child = is_leaf(n->right) ? n->left : n->right;
    
	replace_node(n, child);
	if (n->color == BLACK)
	{
		if (child->color == RED)
			child->color = BLACK;
		else
			delete_case1(child);
	}
	free(n);
}