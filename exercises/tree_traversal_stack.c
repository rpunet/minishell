#include <unistd.h>
#include "../../libftPLUS/includes/libft.h"

typedef struct s_node
{
	int	data;
	struct s_node *left;
	struct s_node *right;
}				t_node;

typedef struct s_stack
{
	t_node			*node;
	struct s_stack *next;
}				t_stack;

t_stack	*new(t_node *node)
{
	t_stack *new_stack = malloc(sizeof(t_stack));
	new_stack->node = node;
	new_stack->next = NULL;
	return new_stack;
}

int	stack_is_empty(t_stack *top)
{
	return (top == NULL) ? 1 : 0;
}

void	push(t_stack **top, t_node *node)
{
	t_stack *slot = new(node);
	slot->next = (*top);
	*top = slot;
	//ft_printf("%d pushed to stack\n", node->data);
}

t_node *pop(t_stack **top)
{
	t_node	*popped;
	t_stack	*temp;

	if (*top == NULL)
		return NULL;
	temp = *top;
	*top = (*top)->next;
	popped = temp->node;
	//ft_printf("%d popped from stack\n", popped->data);
	free(temp);
	return popped;
}

void	in_order_iterative(t_node *root)
{
	t_stack	*stack = NULL;
	t_node	*current = root;
	int		done = 0;

	while (stack != NULL || current != NULL)
	{
		if (current != NULL)
		{
			push(&stack, current);
			current = current->left;
		}
		else
		{
			if (!stack_is_empty(stack))
			{
				current = pop(&stack);			// backtrack al elemento superior del arbol, recuperado del stack
				ft_printf("%d ", current->data);
				current = current->right;
			}
		}
	}
}

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

int	main()
{
	t_node	*root;
	int		i;
	int		array[7] = { 27,14,35,10,19,31,42};

	root = NULL;
	for (int i = 0; i < 7; i++)
		insert(array[i], &root);

	in_order_iterative(root);




	return 0;
}
