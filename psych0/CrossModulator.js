class CrossModulator extends AudioWorkletProcessor
{
    constructor() { super(); this.buffer = null; }
    static get parameterDescriptors()
    {
        return [
        {
            name: "id", //Soon to add Filter Multiplier and LFO...
            defaultValue: 0,
            minValue: 0,
            maxValue: 9999,
            automationRate: "a-rate" //"k-rate"
        }];
    }
    process(inputs, outputs, parameters)
    {
        this.buffer = new Float32Array(inputs[0][0].length);
        for (var s = 0; s < this.buffer.length; ++s) { this.buffer[s] = 1.0; }

        for (var i = 0; i < inputs.length; ++i)
        {
            for (var ch = 0; ch < inputs[i].length; ++ch)
            {
                for (var s = 0; s < inputs[i][ch].length; ++s)
                {
                    this.buffer[s] *= inputs[i][ch][s];
                }
            }
        }

        for (var s = 0; s < this.buffer.length; ++s) { this.buffer[s] /= inputs.length; }

        for (var o = 0; o < outputs.length; ++o)
        {
            for (var ch = 0; ch < outputs[o].length; ++ch)
            {
                for (var s = 0; s < this.buffer.length; ++s)
                {
                    outputs[o][ch][s] = this.buffer[s];
                }
            }
        }

        return true;
    };
}
registerProcessor("CrossModulator", CrossModulator);

/*

        this.input = inputs[this.idx];
        this.output = outputs[this.idx];
        this.channels = 2;
        this.samples = inputs[0][0].length;
        for (this.ch = 0; this.ch < this.channels; ++this.ch)
        {  
            for (this.i = 0; this.i < this.samples; ++this.i)
            {
                outputs[0][this.ch][this.i] = inputs[0][this.ch][this.i]
                                            * inputs[1][this.ch][this.i];
            }
        }
*/