#pragma once

#include <iostream>
#include <string>

//---------------------------------------------------------------------------------------------------------------------------------

#pragma region Vector

//#define VECTOR_DEBUG_INTERACTIVE
//#define VECTOR_DEBUG_AUTOMATIC

template <typename Ttype> class Vector
{
public:
	Vector();	//Default constructor
	Vector(int m_lenght);	//New object constructor
	Vector(const Vector<Ttype>& vectorToCopy);	//Recopy constructor
	~Vector();

	void showArray();
	void interactiveInitializing();
	void fusion(const Vector<Ttype>& vectorToFusion);	//vectorToFusion is a reference in order to preserve free memory ;-)
	void add(Ttype thingToAdd);
	void autoInitializing();

	Ttype getItem(int index);

	int initializing(int index, Ttype content);	//return 0 = No problem ; return 1 = Out of bounds (index > length)
	int getLength();
	int remove(int index);	//return 0 = No problem ; return 1 = Out of bounds (index > length)

	Vector<Ttype> operator+=(const Vector<Ttype>& vectorToFusion);
	Vector<Ttype> operator=(const Vector<Ttype>& vectorToCopy);
	const Vector<Ttype> operator+(const Vector<Ttype>& arrayToAdd);

private:
	int length;
	Ttype *vector;
};

#pragma region Definition of Vector

#pragma region Constructor and Destructor

template <typename Ttype> Vector<Ttype>::Vector()
{
	length = 0;
	vector = new Ttype[0];
}

template <typename Ttype> Vector<Ttype>::Vector(int m_length)
{
	if (m_length < 0)	//Permet d'éviter d'avoir une longueur négative --- Works to have a positive array length
	{
		length = -m_length;
	}
	else
	{
		length = m_length;
	}

	vector = new Ttype[length];	//Initialise le pointeur "vector" en tant que tableau de taille m_length --- Initialize the pointer "vector" like an array

#ifdef VECTOR_DEBUG_INTERACTIVE
	interactiveInitializing();
#endif // DEBUG

#ifdef VECTOR_DEBUG_AUTOMATIC
	autoInitializing();
#endif // DEBUG_AUTOMATIC
}

template <typename Ttype> Vector<Ttype>::Vector(const Vector<Ttype>& vectorToCopy)
{
	length = vectorToCopy.length;
	vector = new Ttype[length];

	for (int i = 0; i < length; i++)	//Permet de copier les éléments de "vectorToCopy.vector" à "this -> vector" --- Copy the elements by "vectorToCopy.vector" to "this -> vector"
	{
		vector[i] = vectorToCopy.vector[i];
	}
}

template <typename Ttype> Vector<Ttype>::~Vector()
{
	delete[] vector;	//Détruit le tableau, pour libérer la mémoire --- Destroy the array, in order to free memory
	length = 0;
}

#pragma endregion

#pragma region Void functions

template <typename Ttype> void Vector<Ttype>::showArray()
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "vector[" << i << "] = " << vector[i] << std::endl;
	}
}

template <typename Ttype> void Vector<Ttype>::interactiveInitializing()
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "Value of vector[" << i << "] = ";
		std::cin >> vector[i];
	}
}

template <typename Ttype> void Vector<Ttype>::fusion(const Vector<Ttype>& vectorToFusion)
{
	Ttype *tempA = new Ttype[length];	//Copie temporaire de l'objet principal --- Temporate copy of the principal object
	Ttype *tempB = new Ttype[vectorToFusion.length];	//Copie temporaire de l'objet à copier --- Temporate copy of the object to copy

	for (int i = 0; i < length; i++)
	{
		tempA[i] = vector[i];
	}

	for (int i = 0; i < vectorToFusion.length; i++)
	{
		tempB[i] = vectorToFusion.vector[i];
	}

	delete[] vector;	//Permet de réinitialiser le tableau (vector::vector) --- Reset the array (vector::vector)

	int totalLength(length + vectorToFusion.length);
	vector = new Ttype[totalLength];	//Créee un nouveau tableau avec la taille adéquate --- Create a new array with the good length

	for (int i = 0; i < length; i++)	//Copie le premier tableau, avec la taille initiale --- Copy the first array, with his initial length
	{
		vector[i] = tempA[i];
	}

	for (int i = 0; i < vectorToFusion.length; i++)	//Copie le second tableau, avec sa taille --- Copy the secound array, with his length
	{
		vector[i + length] = tempB[i];	//Continue la copie du tableau, en partant du dernier emplacement --- Continues the copy of array, by startting at the end
	}

	length = totalLength;	//Modification de la taille du tableau, pour la nouvelle taille --- Modification of array's length, to give the new length

	delete[] tempA;	//Libère la mémoire --- Free memory
	delete[] tempB;	//Idem --- Free memory
}

template <typename Ttype> void Vector<Ttype>::add(Ttype thingToAdd)
{
	Ttype *temp = new Ttype[length + 1];

	for (int i = 0; i < length; i++)
	{
		temp[i] = vector[i];
	}

	delete[] vector;

	length += 1;
	temp[length - 1] = thingToAdd;	//length - 1 car l'index commence de 0 et non de 1 --- length - 1 because the index starts at 0 and not at 1

	vector = new Ttype[length];

	for (int i = 0; i < length; i++)
	{
		vector[i] = temp[i];
	}

	delete[] temp;
}

template <typename Ttype> void Vector<Ttype>::autoInitializing()
{
	for (int i = 0; i < length; i++)
	{
		vector[i] = (Ttype)i;
	}
}

#pragma endregion

#pragma region Ttype functions

template <typename Ttype> Ttype Vector<Ttype>::getItem(int index)
{
	return vector[index];
}

#pragma endregion

#pragma region Int functions

template <typename Ttype> int Vector<Ttype>::initializing(int index, Ttype content)
{
	if (index <= length - 1)
	{
		vector[index] = content;
		return 0;
	}
	else
	{
		return 1;
	}
}

template <typename Ttype> int Vector<Ttype>::getLength()
{
	return length;
}

template <typename Ttype> int Vector<Ttype>::remove(int index)
{
	if (index <= length)
	{
		int length_tempA = length - index - 1;
		int length_tempB = length - index + 1;

		Vector<Ttype> tempA(length_tempA);
		Vector<Ttype> tempB(length_tempB);

		for (int i = 0; i < length_tempA; i++)
		{
			tempA.vector[i] = vector[i];
		}

		for (int i = 0; i < (length_tempB - index); i++)	//TODO : Find a solution to solve correctly reduce the vector
		{
			tempB.vector[i] = vector[i];
		}

		tempA.fusion(tempB);

		*this = tempA;

		return 0;
	}
	else
	{
		return 1;
	}
}

#pragma endregion

#pragma region Operators

template <typename Ttype> Vector<Ttype> Vector<Ttype>::operator+=(const Vector<Ttype>& vectorToFusion)
{
	fusion(vectorToFusion);
	return *this;
}

template <typename Ttype> Vector<Ttype> Vector<Ttype>::operator=(const Vector<Ttype>& vectorToCopy)
{
	length = vectorToCopy.length;

	delete[] vector;
	vector = new Ttype[length];

	for (int i = 0; i < length; i++)	//Permet de copier les éléments de "vectorToCopy.vector" à "this -> vector" --- Copy the elements by "vectorToCopy.vector" to "this -> vector"
	{
		vector[i] = vectorToCopy.vector[i];
	}

	return *this;
}

template <typename Ttype> const Vector<Ttype> Vector<Ttype>::operator+(const Vector<Ttype>& arrayToAdd)
{
	Vector<Ttype> arrayToReturn(0);	//Tableau renvoyé en sortie (Initialisé à 0, pour pouvoir ajouter facilement les tableaux) --- Array which returns in exit (Initialized at 0, to easily add tables)

	arrayToReturn += *this;	//Ajout du tableau du membre de gauche dans le résultat final --- Add the table wich in the left member to the final result
	arrayToReturn += arrayToAdd;	//Ajout du tableau du membre de droite dans le résultat final --- Add the table wich in the right member to the final result

	return arrayToReturn;
}

#pragma endregion

#pragma endregion

#pragma endregion