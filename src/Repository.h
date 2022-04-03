#pragma once

#include "DynamicVector.h"
#include <functional>

/// <summary> A repository of validated entities. Entities are classes with: 'int getId()', 'void setId(int)'. </summary>
template <class TEntity>
class Repository
{
public:
	using Validator = std::function<void(const TEntity& entity)>;
	using Iterable = DynamicVector<TEntity>;

private:
	DynamicVector<TEntity> entities;
	Validator validator;

public:
	/// <summary> Creates a repository that uses the specified validator. </summary>
	/// <param name="validator"> Must be a functor that receives an entity and throws if the entity is invalid. </param>
	Repository(const Validator& validator);

	/// <summary> Get the number of entities in the repository. </summary>
	size_t getCount() const;

private:
	int getFreeId() const;

public:
	/// <summary> Validate, then save the given entity to the repository. </summary>
	/// <param name="id"> The entity will be saved with the specified id. Set to -1 to use the entity's id, -2 to auto assign. Cannot be less than -2 </param>
	/// <param name="entity"> Entity to be saved. </param>
	/// <returns> The id used to save the entity. </returns>
	int save(int id, const TEntity& entity);

	/// <summary> Get the entity with the specified id. </summary>
	/// <param name="id"> Cannot be less than 0. </param>
	/// <returns> If found, a pointer to the entity, otherwise null. Make sure the entity is not deleted before using the pointer. </returns>
	const TEntity* get(int id) const;

	/// <summary> Validate, then update the entity with the specified id. </summary>
	/// <param name="id"> Set to -1 to use the entity's id. Cannot be less than -1. </param>
	/// <param name="entity"> Entity to be copied and replace the old one. </param>
	/// <param name="oldEntity"> If not null, the old entity will be saved to the specified address. </param>
	/// <returns> True if the id was found, otherwise false. </returns>
	bool update(int id, const TEntity& entity, TEntity* oldEntity);

	/// <summary> Delete the entity with the specified id. </summary>
	/// <param name="id"> Cannot be less than 0. </param>
	/// <param name="oldEntity"> If not null, the old entity will be saved to the specified address. </param>
	/// <returns> True if the id was found, otherwise false. </returns>
	bool del(int id, TEntity* oldEntity);

	/// <summary> Get an iterable data structure with all entities. </summary>
	const Iterable& getAll() const;
};

template <class TEntity>
Repository<TEntity>::Repository(const Validator& validator)
{
	this->validator = validator;
}

template <class TEntity>
size_t Repository<TEntity>::getCount() const
{
	return this->entities.getLength();
}

template <class TEntity>
int Repository<TEntity>::getFreeId() const
{
	for (int id = 0; id < INT_MAX; ++id) {
		if (this->get(id) == nullptr)
			return id;
	}
	
	throw std::runtime_error("No more ids left.");
}

template <class TEntity>
int Repository<TEntity>::save(int id, const TEntity& entity)
{
	this->validator(entity);

	if (id == -2)
		id = this->getFreeId();

	if (id == -1)
		id = entity.getId();

	if (id < 0)
		throw std::invalid_argument("Id is invalid.");

	if (this->get(id) != nullptr)
		throw std::logic_error("The id is already in use.");

	this->entities.add(entity);
	this->entities[this->entities.getLength() - 1].setId(id);
	return id;
}

template <class TEntity>
const TEntity* Repository<TEntity>::get(int id) const
{
	for (const TEntity& entity : this->entities) {
		if (entity.getId() == id)
			return &entity;
	}

	return nullptr;
}

template <class TEntity>
bool Repository<TEntity>::update(int id, const TEntity& newEntity, TEntity* oldEntity)
{
	this->validator(newEntity);

	if (id == -1)
		id = newEntity.getId();

	if (id < 0)
		throw std::invalid_argument("Invalid id.");

	for (TEntity& entity : this->entities) {
		if (entity.getId() == id) {
			if (oldEntity != nullptr)
				*oldEntity = std::move(entity);
			entity = newEntity;
			entity.setId(id);
			return true;
		}
	}

	return false;
}

template <class TEntity>
bool Repository<TEntity>::del(int id, TEntity* oldEntity)
{
	if (id < 0)
		throw std::invalid_argument("Invalid id.");

	for (size_t i = 0; i < this->entities.getLength(); ++i) {
		if (this->entities[i].getId() == id) {
			if (oldEntity != nullptr)
				*oldEntity = std::move(this->entities[i]);
			this->entities.removeFast(i);
			return true;
		}
	}

	return false;
}

template <class TEntity>
const DynamicVector<TEntity>& Repository<TEntity>::getAll() const
{
	return this->entities;
}
