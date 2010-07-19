/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2010, Sean D'Epagnier <geckosenator@gmail.com>
 */

#include "chartbase.h"

#include <list>

WX_DECLARE_LIST(wxRealPoint, wxRealPointList);

//    Sight
//----------------------------------------------------------------------------


class Sight : public wxObject
{
public:
   enum BodyLimb {CENTER, UPPER, LOWER};

   Sight(wxString body, BodyLimb bodylimb, wxDateTime datetime,
         double timecertainty, double elevation, double elevationcertainty,
         double azimuth, bool magneticnorth,
         double azimuthcertainty, double height, wxColour colour);
      ~Sight();

      void SetVisible(bool visible = true); ///< set visibility and make points selectable accordingly
      bool IsVisible() { return m_bVisible; }

      bool       m_bVisible;  // should this sight be drawn?
      wxString   m_Body;
      BodyLimb   m_BodyLimb;

      wxDateTime m_DateTime;      // Time for the sight
      float      m_TimeCertainty;

      float      m_Elevation; // Elevation angle in degrees (NaN is valid for all)
      float      m_ElevationCertainty;

      float      m_HeightCorrection, m_LimbCorrection, m_RefractionCorrection, m_ParallaxCorrection;
      float      m_CorrectedElevation; /* after observer height, edge, refraction and parallax */

      float      m_Azimuth;   // azimuth angle in degrees (NaN meaning all angles)
      bool       m_bMagneticNorth; // if azimuth angle is in magnetic coordinages
      float      m_AzimuthCertainty;

      float      m_Height; // Height above sea in meters
      
      wxColour   m_Colour;     // Color of the sight

      void ComputeTraceOneVariable(double center, double certainty, double constantangle,
                                   double stepsize, double &min, double &max, double &step);

      void DrawPolygon(wxDC& dc, ViewPort &pVP, wxRealPointList &area);
      virtual void Draw(wxDC& dc, ViewPort &pVP);

private:
      void BuildElevationLineOfPosition(double elevationmin, double elevationmax, double elevationstep,
                                        double tracestep,
                                        double timemin, double timemax, double timestep);
      void BuildBearingLineOfPosition(double elevationmin, double elevationmax, double elevationstep,
                                      double azimuthmin, double azimuthmax, double azimuthstep,
                                      double timemin, double timemax, double timestep);

      void BodyLocation(wxDateTime time, double &lat, double &lon);

      wxRealPoint DistancePoint(wxDateTime datetime, double elevation, double trace);
      bool BearingPoint(wxDateTime datetime, double elevation, double trace,
                        double &rlat, double &rlon);

      double CalcAngle(wxRealPoint p1, wxRealPoint p2);
      wxRealPointList *MergePoints(wxRealPointList *p1, wxRealPointList *p2);
      wxRealPointList *ReduceToConvexPolygon(wxRealPointList *points);

      std::list<wxRealPointList*> polygons;
};

WX_DECLARE_LIST(Sight, SightList);                    // establish class Sight as list member
