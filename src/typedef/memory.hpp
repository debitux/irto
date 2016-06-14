/*
 *    Copyright 2016 Grégory Muller
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef DBTX_MEMORY_HPP_INCLUDED
#define DBTX_MEMORY_HPP_INCLUDED

#include <memory>

namespace dbtx {
template<typename T> 
using pointer = std::shared_ptr<T>;

template<typename C, typename...Args>
std::shared_ptr<C> new_ptr(Args &&...args) {
        return std::make_shared<C>(std::forward<Args>(args)...);
}

} // namespace dbtx


#endif /* DBTX_MEMORY_HPP_INCLUDED */
