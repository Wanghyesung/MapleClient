#pragma once

#include "WResource.h"

namespace W
{
	class Resources
	{
	public:
		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& _strKey)
		{
			//���ҽ��ʿ��� �����͸� Ž���Ѵ� �����Ͱ� �ִٸ� �ش絥���͸� ��ȯ�ϰ�
			//�����Ͱ� ���ٸ� end�� ��ȯ���ش�.
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter;
			{
				std::lock_guard<mutex> lock(m_mutex);
				//RLock lock(m_lock);
				iter = m_mapResources.find(_strKey);
			}
			
			//ã���� �ϴ� �����Ͱ� �����Ѵٸ�
			//�ش�Ÿ������ ����ȯ�Ͽ� ��ȯ
			if (iter != m_mapResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			//������ ���ٸ� ���� ��ȯ
			return nullptr;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& _strKey, const std::wstring& _strPath)
		{
			// Ű������ Ž��
			std::shared_ptr<T> resource = Resources::Find<T>(_strKey);
			if (resource != nullptr)
				return resource;

			// �ش� ���ҽ��� ���ٸ�
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(_strPath)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(_strKey);
			resource->SetPath(_strPath);

			{
				std::lock_guard<mutex> lock(m_mutex);
				//WLock lock(m_lock);
				m_mapResources.insert(std::make_pair(_strKey, resource));
			}

			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& _strKey, std::shared_ptr<T> _pResource)
		{
			//static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource");
			//WLock lock(m_lock);
			std::lock_guard<mutex> lock(m_mutex);
			m_mapResources.insert(std::make_pair(_strKey, _pResource));
		}

		template <typename T>
		static void Release(const std::wstring& _strKey)
		{
			//WLock lock(m_lock);
			std::lock_guard<mutex> lock(m_mutex);
			m_mapResources.erase(_strKey);
		}
		

	private:
		static RWLock m_lock;
		static std::mutex m_mutex;
		static std::map<std::wstring, std::shared_ptr<Resource>> m_mapResources;
		//���ҽ����� ��쿣 �ε�� ���ҽ��ϳ��� ��ΰ� ���� ������ sharedptr�� ���� ���� �ִ�
		//���ҽ��� ���� �����Ǿ� �׋� ������
	};
}

