#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include "moses/InputType.h"
#include "moses/Syntax/KBestExtractor.h"
#include "moses/Syntax/SVertexBeam.h"
#include "moses/WordsRange.h"

#include "OovHandler.h"
#include "ParserCallback.h"
#include "PChart.h"
#include "SChart.h"

namespace Moses
{
namespace Syntax
{

class SDerivation;
struct SHyperedge;

namespace S2T
{

template<typename Parser>
class Manager
{
 public:
  Manager(const InputType &);

  void Decode();

  // Get the SHyperedge for the 1-best derivation.
  const SHyperedge *GetBestSHyperedge() const;

  void ExtractKBest(
      std::size_t k,
      std::vector<boost::shared_ptr<KBestExtractor::Derivation> > &kBestList,
      bool onlyDistinct=false) const;

  const std::set<Word> &GetUnknownWords() const { return m_oovs; }

 private:
  void FindOovs(const PChart &, std::set<Word> &, std::size_t);

  void InitializeCharts();

  void InitializeParsers(PChart &, std::size_t);

  void RecombineAndSort(const std::vector<SHyperedge*> &, SVertexBeam &);

  void PrunePChart(const SChart::Cell &, PChart::Cell &);

  const InputType &m_source;
  PChart m_pchart;
  SChart m_schart;
  std::set<Word> m_oovs;
  boost::shared_ptr<typename Parser::RuleTrie> m_oovRuleTrie;
  std::vector<boost::shared_ptr<Parser> > m_parsers;
};

}  // S2T
}  // Syntax
}  // Moses

// Implementation
#include "Manager-inl.h"
