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
			//리소스맵에서 데이터를 탐색한다 데이터가 있다면 해당데이터를 반환하고
			//데이터가 없다면 end를 반환해준다.
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = m_mapResources.begin();

			{
				std::lock_guard<std::mutex> lock(m_mutex);
				iter = m_mapResources.find(_strKey);
			}
			//찾고자 하는 데이터가 존재한다면
			//해당타입으로 형변환하여 반환
			if (iter != m_mapResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			//데이터 없다면 널을 반환
			return nullptr;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& _strKey, const std::wstring& _strPath)
		{
			// 키값으로 탐색
			std::shared_ptr<T> resource = Resources::Find<T>(_strKey);
			if (resource != nullptr)
				return resource;

			// 해당 리소스가 없다면
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(_strPath)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(_strKey);
			resource->SetPath(_strPath);

			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mapResources.insert(std::make_pair(_strKey, resource));
			}

			return std::dynamic_pointer_cast<T>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& _strKey, std::shared_ptr<T> _pResource)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_mapResources.insert(std::make_pair(_strKey, _pResource));
		}

		template <typename T>
		static void Release(const std::wstring& _strKey)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_mapResources.erase(_strKey);
		}
		

	private:
		static std::mutex m_mutex;

		static std::map<std::wstring, std::shared_ptr<Resource>> m_mapResources;
		//리소스같은 경우엔 로드된 리소스하나를 모두가 쓰기 때문에 sharedptr이 적합 쓰고 있는
		//리소스가 전부 해제되야 그떄 해제됨
	};
}

