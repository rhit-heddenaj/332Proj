/****************************************************************************
 * Copyright © 2024 Rose-Hulman Institute of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ****************************************************************************/

#ifndef __SLLIST_H
#define __SLLIST_H

/**
 * list_node: A structure for creating nodes in a linked list.
 *
 * @next A pointer to the next node in the list.
 */
struct list_node {
  struct list_node *next;
};

/**
 * init_node() - Initialize a list node.
 *
 * @node The node to initialize.
 */
void init_node(struct list_node *node);

/**
 * add_head() - Add a node to the list at its head.
 *
 * @head  The sentinel head node for the list.
 * @node  The node to add to the list.
 */
void add_head(struct list_node *head, struct list_node *node);

/**
 * add_tail() - Add a node to the list at its tail.
 *
 * @head  The sentinel head node for the list.
 * @node  The node to add to the list.
 */
void add_tail(struct list_node *head, struct list_node *node);

/**
 * del_node() - Delete a node from the list.
 *
 * @head  The sentinel head node for the list.
 * @node  The node to add to the list.
 */
void del_node(struct list_node *head, struct list_node *node);

/**
 * print_list() - Print a list given a custom print function.
 *
 * @head  The sentinel head node for the list.
 * @print_fn  A function pointer to a custom print function.
 */
void print_list(struct list_node *head, void (*print_fn)(struct list_node*));


#endif /* sllist.h */
