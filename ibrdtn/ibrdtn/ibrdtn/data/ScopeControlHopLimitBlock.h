/*
 * ScopeControlHopLimitBlock.h
 *
 * Copyright (C) 2011 IBR, TU Braunschweig
 *
 * Written-by: Johannes Morgenroth <morgenroth@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <ibrdtn/data/Block.h>
#include <ibrdtn/data/SDNV.h>
#include <ibrdtn/data/ExtensionBlock.h>

#ifndef SCOPECONTROLHOPLIMITBLOCK_H_
#define SCOPECONTROLHOPLIMITBLOCK_H_

namespace dtn
{
	namespace data
	{
		class ScopeControlHopLimitBlock : public dtn::data::Block
		{
		public:
			class Factory : public dtn::data::ExtensionBlock::Factory
			{
			public:
				Factory() : dtn::data::ExtensionBlock::Factory(ScopeControlHopLimitBlock::BLOCK_TYPE) {};
				virtual ~Factory() {};
				virtual dtn::data::Block* create();
			};

			enum { BLOCK_TYPE = (dtn::data::block_t)199 };

			ScopeControlHopLimitBlock();
			virtual ~ScopeControlHopLimitBlock();

			size_t getHopsToLive() const;
			void increment(size_t hops = 1);
			void setLimit(size_t hops);

			virtual size_t getLength() const;
			virtual std::ostream &serialize(std::ostream &stream, size_t &length) const;
			virtual std::istream &deserialize(std::istream &stream, const size_t length);

		private:
			dtn::data::SDNV _count;
			dtn::data::SDNV _limit;
		};

		/**
		 * This creates a static block factory
		 */
		static ScopeControlHopLimitBlock::Factory __ScopeControlHopLimitBlockFactory__;
	} /* namespace data */
} /* namespace dtn */
#endif /* SCOPECONTROLHOPLIMITBLOCK_H_ */
