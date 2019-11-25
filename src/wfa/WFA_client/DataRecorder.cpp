//
// Created by lw on 20.03.19.
//
#define ORIGINAL_WFA_SKD

#include <chrono>
#include "DataRecorder.h"

void DataRecorder::init_columns(std::ofstream &csv_file) {
  csv_file << "Info.Time,"
          << "CurrentJob.Id,"
           << "CurrentJob.LayerCountCurrent,"
           << "CurrentJob.LayerCountTarget,"
           << "CurrentJob.LayerThickness,"
           << "CurrentJob.MaterialName,"
           << "CurrentJob.OrderId,"
           << "CurrentJob.Starter,"
           << "CurrentJob.Times.BuildStart,"
           << "CurrentJob.Times.CoolDownStart,"
           << "CurrentJob.Times.JobEnd,"
           << "Info.Brand,"
           << "Info.HostName,"
           << "Info.Id,"
           << "Info.Model,"
           << "Info.ProcessState,"
           << "Info.ProcessStateWFA,"
           << "Info.ProcessStateSemiE10,"
           << "Info.Type,"
           << "Sensors.BuildingPlatform.Position,"
           << "Sensors.BuildingPlatform.Speed,"
           << "Sensors.BuildingPlatform.Temperature,"
           << "Sensors.CollectorPlatform.Position,"
           << "Sensors.Dispenser.FillLevel,"
           << "Sensors.Dispenser.LastDosingCount,"
           << "Sensors.Dispenser.Position,"
           << "Sensors.Dispenser.Speed,"
           << "Sensors.EU1.Temperature,"
           << "Sensors.EU2.Temperature,"
           << "Sensors.EU3.Temperature,"
           << "Sensors.EU4.Temperature,"
           << "Sensors.ProcessChamber.InertGasType,"
           << "Sensors.ProcessChamber.O2ConcentrationBottom,"
           << "Sensors.ProcessChamber.O2ConcentrationTop,"
           << "Sensors.ProcessChamber.RelativePressure,"
           << "Sensors.ProcessChamber.Temperature,"
           << "Sensors.RecirculatingFilterSystem.O2Concentration,"
           << "Sensors.RecirculatingFilterSystem.Pressure,"
           << "Sensors.Recoater.Position,"
           << "Sensors.Recoater.Speed,"
           << "Sensors.Turbine.Pressure,"
           << "Environment.HumidityRelative,"
           << "Environment.Temperature"
           << "\n";
}

void DataRecorder::write_to_row(std::ofstream &csv_file,
                                const OpcUa::Node &node,
                                const OpcUa::DataValue &value) {
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Id;)") {
        csv_file <<"," <<value.Value.ToString();
    }
    if (node.ToString() ==
        "Node(ns=2;s=WFA.Machine.CurrentJob.LayerCountCurrent;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() ==
        "Node(ns=2;s=WFA.Machine.CurrentJob.LayerCountTarget;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node`.ToString() ==
        "Node(ns=2;s=WFA.Machine.CurrentJob.LayerThickness;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.MaterialName;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.OrderId;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Starter;)") {
        csv_file << "," << value.Value.ToString() ;
    }
#ifdef ORIGINAL_WFA_SKD
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Times.BuildStart;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Times.CoolDownStart;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Times.JobEnd;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.Time;)") {
        csv_file  << value.Value.ToString() ;
    }
#else
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Times.BuildStart;)") {
        csv_file  << ","<< "BuildStart" ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Times.CoolDownStart;)") {
        csv_file  << ","<< "Cooldown" ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.CurrentJob.Times.JobEnd;)") {
        csv_file  << ","<< "JobEnd" ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.Time;)") {
        csv_file  << "Time" ;
    }
#endif

    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.Brand;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.Id;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.HostName;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.Model;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.ProcessState;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.ProcessStateWFA;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.ProcessStateSemiE10;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Info.Type;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.RecFilSys.O2Concentration;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Recoater.Position;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Recoater.Speed;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Turbine.Pressure;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.BuildingPlatform.Position;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.BuildingPlatform.Speed;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.BuildingPlatform.Temperature;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.CollectorPlatform.Position;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Dispenser.FillLevel;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Dispenser.LastDosingCount;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Dispenser.Position;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.Dispenser.Speed;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ExposureUnits.ExposureUnit1.Temperature;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ExposureUnits.ExposureUnit2.Temperature;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ExposureUnits.ExposureUnit3.Temperature;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ExposureUnits.ExposureUnit4.Temperature;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ProcessChamber.InertGasType;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ProcessChamber.O2ConcentrationBottom;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ProcessChamber.O2ConcentrationTop;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ProcessChamber.RelativePressure;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.ProcessChamber.Temperature;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.RecirculatingFilterSystem.O2Concentration;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Sensors.RecirculatingFilterSystem.FilterPressure;)") {
        csv_file << "," << value.Value.ToString();
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Environment.HumidityRelative;)") {
        csv_file << "," << value.Value.ToString() ;
    }
    if (node.ToString() == "Node(ns=2;s=WFA.Machine.Environment.Temperature;)") {
        csv_file << "," << value.Value.ToString()<<"\n";
    }
}
