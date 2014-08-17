import java.beans.PropertyVetoException;
import java.util.Locale;

import javax.speech.AudioException;
import javax.speech.Central;
import javax.speech.EngineException;
import javax.speech.EngineStateError;
import javax.speech.synthesis.Synthesizer;
import javax.speech.synthesis.SynthesizerModeDesc;
import javax.speech.synthesis.Voice;

public class SynthesizerFactory {

    public static Synthesizer getSynthesizer() throws IllegalArgumentException,
            EngineException, AudioException, EngineStateError,
            PropertyVetoException {
        SynthesizerModeDesc desc = new SynthesizerModeDesc(null, // engine name
                "general", // mode name
                Locale.US, // locale
                null, // running
                null); // voice
        Synthesizer synthesizer = Central.createSynthesizer(desc);
        if (synthesizer == null) return null;
        synthesizer.allocate();
        synthesizer.resume();
        desc = (SynthesizerModeDesc) synthesizer.getEngineModeDesc();
        Voice[] voices = desc.getVoices();
        Voice voice = null;
        for (int i = 0; i < voices.length; i++) {
            if (voices[i].getName().equals("kevin16")) {
                voice = voices[i];
                break;
            }
        }
        synthesizer.getSynthesizerProperties().setVoice(voice);
        return synthesizer;

    }
}
