/* ///////////////////////////////////////////////////////////////////////
 * File:		uga_base.h		
 *
 * Created:		08.09.14
 * Updated:		08.09.14
 *
 * Brief:		The Micro-population Genetic Algoritm Base Class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_UGA_BASE_H
#define EXTL_INTELLIGENCE_GA_UGA_BASE_H

/*!\file uga_base.h
 * \brief The Genetic Algoritm Class
 */
#ifndef __cplusplus
#	error uga_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fitness_traits_base class
 * 
 * \param D The derived type
 * \param Ga The ga type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k D
		,	typename_param_k Ga
		>
class uga_base
	: private uncopyable<uga_base<D, Ga> >
{
	/// \name Types
	/// @{
	public:
		typedef D														derived_type;
		typedef Ga														ga_type;
		typedef uga_base												class_type;
		typedef typename_type_k ga_type::ga_traits_type					ga_traits_type;
		typedef typename_type_k ga_type::size_type						size_type;
		typedef typename_type_k ga_type::bool_type						bool_type;
		typedef typename_type_k ga_type::float_type						float_type;
		typedef typename_type_k ga_type::index_type						index_type;
		typedef typename_type_k ga_type::int_type						int_type;
		typedef typename_type_k ga_type::population_type				population_type;
		typedef typename_type_k ga_type::individual_type				individual_type;
	/// @}
		
	/// @{
	private:
		ga_traits_type													m_ga_traits;
		population_type													m_pop;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// Generates a best population
		bool_type generate(population_type& pop)
		{
			// initialize uga_traits
			ga_traits().init_traits();

			// invariance
			EXTL_ASSERT(ga_traits().is_valid());
			EXTL_ASSERT(pop.size() > 0);
			if (!ga_traits().is_valid() || pop.size() <= 0) return e_false_v;

			// initialize child population
			population_type child_pop = pop;
			population_type* pchild_pop = &child_pop;
			population_type* pparent_pop = &pop;

			size_type max_g = ga_traits().max_g();
			for (index_type i = 0; i < max_g; ++i)
			{
				// generate better individual using ga
				if (!derive().ga().generate(*pparent_pop)) return e_false_v;

				// report detail for debugging
				//report(*pparent_pop);

				// update fitness for this ga_traits
				ga_traits().fitness(*pparent_pop);

				// find out the best result
				if (ga_traits().is_stop(*pparent_pop)) break;

				// reserve best individual
				ga_traits().init_pop(*pchild_pop);
				ga_traits().fitness(*pchild_pop);
				pchild_pop->worst() = pparent_pop->best();

				// next generation
				pchild_pop->generation(i + 1);
				std_swap(pchild_pop, pparent_pop);
			}

			// update this population and return it
			ga_traits().fitness(*pparent_pop);
			if (pparent_pop != &pop) pop = *pparent_pop;

		#ifdef EXTL_INTELLIGENCE_GA_UGA_TEST_ENABLE
			// report detail for debugging
			report(pop);
		#endif

			EXTL_ASSERT(ga_traits().is_valid());
			return e_true_v;
		}
		/// Generates a best population
		bool_type generate()
		{
			// initialize population
			m_pop.resize(ga_traits().pop_size());
			ga_traits().init_pop(m_pop);

			return generate(m_pop);
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// Returns const ga_traits
		ga_traits_type const&	ga_traits() const	{ return m_ga_traits;				}
		/// Returns ga_traits
		ga_traits_type&			ga_traits()			{ return m_ga_traits;				}

		/// Returns the best individual
		individual_type const&	best() const		{ return population().best();		}
		/// Returns the population at last generation  
		population_type const&	population() const	{ return m_pop;						}	

		/// Returns the generation of the best population
		size_type const			generation() const	{ return population().generation();	}
	/// @}

	private:
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		derived_type&		derive() 		{ return static_cast<derived_type&>(*this);			}

	private:
	#ifdef EXTL_INTELLIGENCE_GA_UGA_TEST_ENABLE
		void report(population_type const& pop)
		{
			EXTL_TEST_TRACE(_T("g:%d fmin:%f fmax:%f fsum:%f favg:%f"), 
				pop.generation(), pop.fmin(), pop.fmax(), pop.fsum(), pop.favg());

			EXTL_TEST_TRACE(_T("best: x=%f fvalue:%f"), 
				pop.best().value(0), ga_traits().fvalue(pop.best()));

			/*EXTL_TEST_TRACE(_T("detail:"));
			for (size_type i = 0; i < pop.size(); ++i)
			{
				EXTL_TEST_TRACE(
					_T("x=%f fvalue:%f fit:%f pro:%f"), 
					pop.individual(i).value(0),
					uga_traits().fvalue(pop.individual(i)), 
					pop.individual(i).fitness(),
					pop.individual(i).probability());
			}*/

			EXTL_TEST_TRACE(_T("\n"));
		}
	#endif
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_UGA_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
