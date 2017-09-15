//
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_INTERPOLATINGANTENNA_H
#define __INET_INTERPOLATINGANTENNA_H

#include "inet/physicallayer/base/packetlevel/AntennaBase.h"

namespace inet {

namespace physicallayer {

class INET_API InterpolatingAntenna : public AntennaBase
{
  protected:
    class AntennaParameters
    {
      protected:
        double minGain = NaN;
        double maxGain = NaN;
        std::map<double, double> elevationGainMap;
        std::map<double, double> headingGainMap;
        std::map<double, double> bankGainMap;

      protected:
        virtual void parseMap(std::map<double, double>& gainMap, const char *text);

      public:
        virtual double getMinGain() const { return minGain; }
        virtual double getMaxGain() const { return maxGain; }
        virtual const std::map<double, double>& getElevationGains() const { return elevationGainMap; }
        virtual const std::map<double, double>& getHeadingGains() const { return headingGainMap; }
        virtual const std::map<double, double>& getBankGains() const { return bankGainMap; }
        virtual void parseElevationGains(const char *text) { parseMap(elevationGainMap, text); }
        virtual void parseHeadingGains(const char *text) { parseMap(headingGainMap, text); }
        virtual void parseBankGains(const char *text) { parseMap(bankGainMap, text); }
    };

    class AntennaGain : public IAntennaGain
    {
      protected:
        AntennaParameters parameters;

      public:
        AntennaGain() = default;
        AntennaGain(const AntennaParameters&);
        virtual IAntennaGain *duplicate() const override { return new AntennaGain(*this); }
        virtual double getMinGain() const { return parameters.getMinGain(); }
        virtual double getMaxGain() const override { return parameters.getMaxGain(); }
        virtual double computeGain(const std::map<double, double>& gainMap, double angle) const;
        virtual double computeGain(const EulerAngles direction) const override;

        friend class InterpolatingAntenna;
    };

    AntennaGain gain;

  protected:
    virtual void initialize(int stage) override;

  public:
    InterpolatingAntenna();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual const IAntennaGain *getGain() const override { return &gain; }
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_INTERPOLATINGANTENNA_H

