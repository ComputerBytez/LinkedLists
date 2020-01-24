/* A linked list implematnation
 *
 * Copyright Nathan Black 2019-2020
 */
 
namespace ComputerBytez
{

  template<class T>
  class LinkedList
  {
  private:
    //typedef int T;

    class Node
    {
    public:

      T value;
      Node *next;

        Node ()
      {
	next = nullptr;
      }

      Node (const T & v)
      {
	value = v;
	next = nullptr;
      }

      // Creates a new copy of a given Node, and returns it
      static Node *Copy (Node * n)
      {
	Node *result = new Node;

	if (n != nullptr)
	  {
	    result->value = n->value;

	    // if we have a value in n->next
	    if (n->next != nullptr)
	      {
		result->next = Copy (n->next);
	      }
	  }

	// return the result
	return result;
      }

      static void DeleteNode (Node * n)
      {
	if (n == nullptr)
	  {
	    // nothing to delete
	    return;
	  }

	// Delete everything after us
	DeleteNode (n->next);

	// now delete us
	delete n;

      }
    };

    Node *head;

  public:

    LinkedList ()
    {
      head = nullptr;
    }

    LinkedList (const LinkedList & other)
    {
      head = Node::Copy (other.head);
    }

    LinkedList (LinkedList && other)
    {
      head = other.head;
      other.head = nullptr;
    }


    LinkedList & operator= (const LinkedList & other)
    {
      // clear our old value out
      Node::DeleteNode (head);

      head = Node::Copy (other.head);

      return *this;
    }

    LinkedList & operator= (LinkedList && other)
    {
      head = other.head;
      other.head = nullptr;

      return *this;
    }


    ~LinkedList ()
    {
      Node *tmp = nullptr;

      while (head != nullptr)
	{
	  tmp = head;
	  head = head->next;
	  delete tmp;
	}
    }

    // Our add functions
    void addFront (T val)
    {
      Node *newNode = new Node (val);

      newNode->next = head;

      head = newNode;
    }

    void addBack (T val)
    {
      // First, make sure our pointer is not nullptr
      if (head == nullptr)
	{
	  // The list is empty, so just add it to the front
	  head = new Node (val);
	}
      else
	{
	  Node *toAdd = new Node (val);
	  Node *last = head;
	  // find the last item in the list
	  while (last->next != nullptr)
	    {
	      last = last->next;
	    }
	  // Now we have the last item, add to the end
	  last->next = toAdd;
	}
    }

    // The Delete functions

    void deleteFront ()
    {
      if (head == nullptr)
	{
	  // There is no list; nothing to delete
	  // We should probably throw some sort of exception here
	  // Instead, in the mean time, let's just return here 
	  return;		// we could return a boolean status, I suppose
	}
      else
	{

	  Node *toDelete = head;	// since we are getting rid of the front item in the list

	  // now actually remove the node from the list
	  head = head->next;

	  // deallocate the unused memory
	  delete toDelete;
	}
    }

    void deleteBack ()
    {
      // First, make sure our pointer is not nullptr
      if (head == nullptr)
	{
	  // Again, there is no list; nothing to delete
	  // As before, we should probably throw some sort of exception here
	  // But again, instead, we're just going to return here 
	  return;		// we could still return a boolean status, I suppose
	}
      else if (head->next == nullptr)
	{
	  // Here we are in an interesting situation
	  // here, the back is the front, so let's just delete the front

	  // This is basically the same as deleting the front as before
	  Node *toDelete = head;

	  // now actually remove the node from the list
	  head = head->next;

	  // deallocate the unused memory
	  delete toDelete;

	}
      else
	{

	  Node *toDeletePrevious = head;
	  // find the last item in the list
	  while (toDeletePrevious->next->next != nullptr)
	    {
	      toDeletePrevious = toDeletePrevious->next;
	    }

	  // Now we have the last item, add to the end
	  // Let's delete the last item
	  delete toDeletePrevious->next;
	  // Now let's teminate the list
	  toDeletePrevious->next = nullptr;
	}
    }

    // Middle functions

    T & at (unsigned int n)
    {
      Node *tmp = head;
      // find the nth node
      for (int i = 0; i < n && tmp != nullptr; i++)
	{
	  tmp = tmp->next;
	}

      // if we get nullptr, we have no choice but to throw an exception.
      // I suppose there are other options, but this is the cleanest way
      // I can think of
      if (tmp == nullptr)
	{
	  throw ("Out of Range");
	}

      // not return the value
      return tmp->value;
    }

    const T & at (unsigned int n) const
    {
      Node *tmp = head;
      // find the nth node
      for (int i = 0; i < n && tmp != nullptr; i++)
	{
	  tmp = tmp->next;
	}

      // if we get nullptr, we have no choice but to throw an exception.
      // I suppose there are other options, but this is the cleanest way
      // I can think of
      if (tmp == nullptr)
	{
	  throw ("Out of Range");
	}

      // not return the value
      return tmp->value;
    }

    // note: Function becomes the item at position `n`
    void addAt (int n, T val)
    {
      if (n == 0)
	{
	  // Basically, we would be adding to the front, so let's do that
	  addFront (val);
	}
      else
	{
	  // Otherwise, continue adding
	  Node *tmp = head;

	  // find the n-1th node
	  for (int i = 0; i < n - 1 && tmp != nullptr; i++)
	    {
	      tmp = tmp->next;
	    }

	  // Again, if we get nullptr, we have (almost, in this case) no choice but to throw an exception.
	  if (tmp == nullptr)
	    {
	      throw ("Out of Range");
	    }
	  else if (tmp->next == nullptr)
	    {
	      // We want to become the `n`th item in the list
	      // If we add properly here, we will become the `n`th item in the list
	      // However, this also means the number the caller gave us is technically
	      // currently out of bounds, even though it will be in bounds shortly.
	      // However, for consitstency, we will throw an exception, just so we can say:
	      // "n must be a position that exists currently in the list
	      throw ("Out of Range");
	    }

	  // Okay, so now we can actually add the item:
	  Node *toAdd = new Node (val);

	  // Fix the link to the next node
	  toAdd->next = tmp->next;

	  // Okay, now actually insert into the list
	  tmp->next = toAdd;

	  // and done

	}
    }

    void deleteAt (int n)
    {
      if (n == 0)
	{
	  // Similarly to addAt(), if n is 0, we can basically do the same thing as deleteFront(), so why not just call it?
	  deleteFront ();
	}
      else
	{
	  // Otherwise, continue deleting
	  Node *tmp = head;

	  // find the n-1th node
	  for (int i = 0; i < n - 1 && tmp != nullptr; i++)
	    {
	      tmp = tmp->next;
	    }

	  // Again, if we get nullptr, we have (almost, in this case) no choice but to throw an exception.
	  if (tmp == nullptr)
	    {
	      throw ("Out of Range");
	    }
	  else if (tmp->next == nullptr)
	    {
	      // if the next item is nullptr, we can't really do anything because the `n`th
	      // position also doesn't exist, so throw an exception
	      throw ("Out of Range");
	    }

	  // Okay, so now we can actually start deleting:
	  Node *toDelete = tmp->next;

	  // Fix the link to the next node
	  tmp->next = toDelete->next;

	  // Okay, now actually delete the item's memory
	  delete toDelete;

	  // and done

	}

    }

    // a size function
    int size () const
    {
      Node *tmp = head;
      int size = 0;


      // count the size of the list
      for (size = 0; tmp != nullptr; size++)
	{
	  tmp = tmp->next;
	}

      // now return the size we generated
      return size;
    }

    // our operators
    T & operator[](unsigned int n)
    {
      return at (n);
    }

    const T & operator[] (unsigned int n) const
    {
      return at (n);
    }

    // stream operators

    // out
    friend std::ostream & operator<< (std::ostream & stream, const LinkedList & list)
    {
      unsigned int size = list.size ();

      stream << "(";

      for (int i = 0; i < size; i++)
	{
	  stream << list[i];
	  // if we're not the last time
	  if (i != size - 1)
	    {
	      // we wouldn't want a trailing coma
	      stream << ", ";
	    }
	}

      stream << ")";

      return stream;
    }

    friend std::istream& operator>>(std::istream& stream, LinkedList& list) {
	    T tmp;

    	if(stream >> tmp) {
            list.addBack(tmp);	
        }
	    return stream;
    }

  };
} // end namespace ComputerBytez
