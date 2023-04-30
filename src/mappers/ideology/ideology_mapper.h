#ifndef SRC_MAPPERS_IDEOLOGY_IDEOLOGYMAPPER_H
#define SRC_MAPPERS_IDEOLOGY_IDEOLOGYMAPPER_H



#include <map>
#include <string>



namespace mappers
{

using ideology_points_map = std::map<std::string, int>;


class IdeologyMapper
{
  public:
   explicit IdeologyMapper(std::map<std::string, ideology_points_map> rules): rules_(std::move(rules)) {}

   [[nodiscard]] std::string GetRulingIdeology(const std::set<std::string>& current_laws) const;

  private:
   std::map<std::string, ideology_points_map> rules_;
};

}  // namespace mappers



#endif  // SRC_MAPPERS_IDEOLOGY_IDEOLOGYMAPPER_H