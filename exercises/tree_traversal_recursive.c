#include <unistd.h>
#include "../../libftPLUS/includes/libft.h"

typedef struct s_node
{
	int	data;
	struct s_node *left;
	struct s_node *right;
}				t_node;

void	insert(int data, t_node **root)
{
	t_node *node;
	t_node *current;
	t_node *parent;

	node = malloc(sizeof(t_node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	if (*root == NULL)
		*root = node;
	else
	{
		current = *root;
		while (1)
		{
			parent = current;
			if (data < parent->data)
			{
				current = current->left;
				if (current == NULL)
				{
					parent->left = node;
					return ;
				}
			}
			else
			{
				current = current->right;
				if (current == NULL)
				{
					parent->right = node;
					return ;
				}
			}
		}
	}
}

t_node	*search(int data, t_node *current)
{
	while (current->data != data)
	{
		ft_printf("[%d]", current->data);
		if (data < current->data)
			current = current->left;
		else
			current = current->right;
		if (current == NULL)
			return NULL;
	}
	return current;
}

void	pre_order_traversal(t_node *root)
{
	if (root != NULL)
	{
		ft_printf("%d ", root->data);
		pre_order_traversal(root->left);
		pre_order_traversal(root->right);
	}
}
void	in_order_traversal(t_node *root)
{
	if (root != NULL)
	{
		in_order_traversal(root->left);
		ft_printf("%d ", root->data);
		in_order_traversal(root->right);
	}
}
void	post_order_traversal(t_node *root)
{
	if (root != NULL)
	{
		post_order_traversal(root->left);
		post_order_traversal(root->right);
		ft_printf("%d ", root->data);
	}
}

int	main()
{
	t_node	*root;
	int		i;
	int		array[7] = { 27,14,35,10,19,31,42};

	root = NULL;
	for (int i = 0; i < 7; i++)
		insert(array[i], &root);

	ft_printf("preorder traversal:   ");
	pre_order_traversal(root);
	ft_printf("\ninorder traversal:    ");
	in_order_traversal(root);
	ft_printf("\npostorder traversal:  ");
	post_order_traversal(root);

	i = 42;
	ft_printf("\n\nSearching num %d: ", i);
	t_node	*tmp;
	tmp = search(i, root);
	if (tmp != NULL)
		ft_printf(" >> %d\n", tmp->data);
	else
		ft_printf("X: %d not found\n", i);

	i = 47;
	ft_printf("\n\nSearching num %d: ", i);
	tmp = search(i, root);
	if (tmp != NULL)
		ft_printf(" >> %d\n", tmp->data);
	else
		ft_printf("X: %d not found\n", i);
	return 0;
}
