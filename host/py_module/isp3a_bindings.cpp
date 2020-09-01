#include "capture_af_bindings.hpp"

//project
#include "metadata/isp3a_metadata.hpp"
#include "host_capture_command.hpp"

// Binding for CaptureMetadata POD
namespace py = pybind11;

extern std::unique_ptr<HostCaptureCommand> g_host_caputure_command;


static void send_isp_3a_command(Isp3A_CamId camera_id, Isp3A_Commands command_id,
                                const std::string &extra_args) {
    if(g_host_caputure_command != nullptr) {
        g_host_caputure_command->sendIsp3A(camera_id, command_id, extra_args.c_str());
    }
}

void init_binding_isp3a(pybind11::module& m) {

    py::enum_<Isp3A_CamId>(m, "Cam3A")
        .value("RGB",   Isp3A_CamId::CAM_RGB)
        .value("Left",  Isp3A_CamId::CAM_LEFT)
        .value("Right", Isp3A_CamId::CAM_RIGHT)
    ;

    py::enum_<Isp3A_Commands>(m, "Isp3A")
        .value("CMD_START_STREAM",             Isp3A_Commands::CMD_START_STREAM)
        .value("CMD_STOP_STREAM",              Isp3A_Commands::CMD_STOP_STREAM)
        .value("CMD_REQ_STILL",                Isp3A_Commands::CMD_REQ_STILL)
        .value("CMD_MOV_LENS",                 Isp3A_Commands::CMD_MOV_LENS)
        .value("CMD_FOCUS_TRIGGER",            Isp3A_Commands::CMD_FOCUS_TRIGGER)
        .value("CMD_AE_MANUAL",                Isp3A_Commands::CMD_AE_MANUAL)
        .value("CMD_AE_AUTO",                  Isp3A_Commands::CMD_AE_AUTO)
        .value("CMD_SET_AWB_MODE",             Isp3A_Commands::CMD_SET_AWB_MODE)
        .value("CMD_SCENE_MODES",              Isp3A_Commands::CMD_SCENE_MODES)
        .value("CMD_ANTIBANDING_MODES",        Isp3A_Commands::CMD_ANTIBANDING_MODES)
        .value("CMD_EXPOSURE_COMPENSATION",    Isp3A_Commands::CMD_EXPOSURE_COMPENSATION)
        .value("CMD_AE_LOCK",                  Isp3A_Commands::CMD_AE_LOCK)
        .value("CMD_AE_TARGET_FPS_RANGE",      Isp3A_Commands::CMD_AE_TARGET_FPS_RANGE)
        .value("CMD_AWB_LOCK",                 Isp3A_Commands::CMD_AWB_LOCK)
        .value("CMD_CAPTURE_INTENT",           Isp3A_Commands::CMD_CAPTURE_INTENT)
        .value("CMD_CONTROL_MODE",             Isp3A_Commands::CMD_CONTROL_MODE)
        .value("CMD_FRAME_DURATION",           Isp3A_Commands::CMD_FRAME_DURATION)
        .value("CMD_SENSITIVITY",              Isp3A_Commands::CMD_SENSITIVITY)
        .value("CMD_EFFECT_MODE",              Isp3A_Commands::CMD_EFFECT_MODE)
        .value("CMD_AF_MODE",                  Isp3A_Commands::CMD_AF_MODE)
        .value("CMD_NOISE_REDUCTION_STRENGTH", Isp3A_Commands::CMD_NOISE_REDUCTION_STRENGTH)
        .value("CMD_SATURATION",               Isp3A_Commands::CMD_SATURATION)
        .value("CMD_BRIGHTNESS",               Isp3A_Commands::CMD_BRIGHTNESS)
        .value("CMD_STREAM_FORMAT",            Isp3A_Commands::CMD_STREAM_FORMAT)
        .value("CMD_CAM_RESOLUTION",           Isp3A_Commands::CMD_CAM_RESOLUTION)
        .value("CMD_SHARPNESS",                Isp3A_Commands::CMD_SHARPNESS)
        .value("CMD_CUST_USECASE",             Isp3A_Commands::CMD_CUST_USECASE)
        .value("CMD_CUST_CAPT_MODE",           Isp3A_Commands::CMD_CUST_CAPT_MODE)
        .value("CMD_CUST_EXP_BRACKETS",        Isp3A_Commands::CMD_CUST_EXP_BRACKETS)
        .value("CMD_CUST_CAPTURE",             Isp3A_Commands::CMD_CUST_CAPTURE)
        .value("CMD_CONTRAST",                 Isp3A_Commands::CMD_CONTRAST)
        .value("CMD_AE_REGION",                Isp3A_Commands::CMD_AE_REGION)
        .value("CMD_AF_REGION",                Isp3A_Commands::CMD_AF_REGION)
        .value("CMD_LUMA_DENOISE",             Isp3A_Commands::CMD_LUMA_DENOISE)
        .value("CMD_CHROMA_DENOISE",           Isp3A_Commands::CMD_CHROMA_DENOISE)
    ;

    // depthai.send_isp_3a_command(Isp3A_CamId, Isp3A_Commands, str_extra_args_space_separated)
    m.def(
        "send_isp_3a_command",
        &send_isp_3a_command,
        "Function to send an ISP 3A camera command",
        py::arg("camera_id"),
        py::arg("command_id"),
        py::arg("extra_args")
    );
}
